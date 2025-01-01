use std::collections::{HashMap, HashSet};

use crate::{
    ast::{Command, Location},
    message::{DisplayMessage, Message, MessageSeverity},
    program::Program,
};

use super::NoRecursiveCalls;

/**
 *   Can be used to detect recursion for procedures defined after
 *   the caller procedure  
 */
impl NoRecursiveCalls {
    pub fn detect_recursive_calls(&self, prog: &Program) -> Result<(), ()> {
        let call_graph = self.build_call_graph(prog);
        let call_locations = self.build_call_locations(prog);
        let mut recursive_calls = Vec::new();

        #[derive(Debug, Clone)]
        pub struct RecursiveCallInfo {
            pub procedure_name: String,
            pub recursive_path: Vec<String>,
            pub location: Location,
        }

        for (_, procedure) in &prog.ast.procedures {
            let mut visited_procedures = HashSet::new();
            if self.is_recursive(&call_graph, &procedure.name, &mut visited_procedures) {
                let recursive_path: Vec<String> = visited_procedures.into_iter().collect();

                if let Some(first_recursive_call_location) = self
                    .find_first_recursive_call_location(
                        &procedure.name,
                        &call_graph,
                        &call_locations,
                    )
                {
                    recursive_calls.push(RecursiveCallInfo {
                        procedure_name: procedure.name.clone(),
                        recursive_path,
                        location: first_recursive_call_location,
                    });
                }
            }
        }

        if recursive_calls.len() == 0 {
            return Ok(());
        }

        prog.print_message(Message::CodeMessage {
            severity: MessageSeverity::ERROR,
            message: format!(
                "recursive calls are not allowed {} : [{}]",
                recursive_calls[0].procedure_name,
                recursive_calls[0].recursive_path.join(" <- ")
            )
            .as_str(),
            location: recursive_calls[0].location.clone(),
        });

        return Err(());
    }
    fn build_call_graph(&self, prog: &Program) -> HashMap<String, HashSet<String>> {
        let mut graph = HashMap::new();

        for (_, procedure) in &prog.ast.procedures {
            graph
                .entry(procedure.name.clone())
                .or_insert_with(HashSet::new);

            let calls = self.find_procedure_calls(&procedure.commands);
            graph.get_mut(&procedure.name).unwrap().extend(calls);
        }

        return graph;
    }

    fn build_call_locations(&self, prog: &Program) -> HashMap<(String, String), Location> {
        let mut locations = HashMap::new();

        for (_, procedure) in &prog.ast.procedures {
            self.record_call_locations(&procedure.name, &procedure.commands, &mut locations);
        }

        return locations;
    }

    fn record_call_locations(
        &self,
        current_proc: &str,
        commands: &[Command],
        locations: &mut HashMap<(String, String), Location>,
    ) {
        for command in commands {
            match command {
                Command::ProcedureCall {
                    proc_name,
                    location,
                    ..
                } => {
                    locations.insert(
                        (current_proc.to_string(), proc_name.clone()),
                        location.clone(),
                    );
                }
                Command::IfElse {
                    then_commands,
                    else_commands,
                    ..
                } => {
                    self.record_call_locations(current_proc, then_commands, locations);
                    self.record_call_locations(current_proc, else_commands, locations);
                }
                Command::If { then_commands, .. } => {
                    self.record_call_locations(current_proc, then_commands, locations);
                }
                Command::While { commands, .. } => {
                    self.record_call_locations(current_proc, commands, locations);
                }
                Command::Repeat { commands, .. } => {
                    self.record_call_locations(current_proc, commands, locations);
                }
                Command::For { commands, .. } => {
                    self.record_call_locations(current_proc, commands, locations);
                }
                _ => {}
            }
        }
    }

    fn find_first_recursive_call_location(
        &self,
        procedure_name: &str,
        call_graph: &HashMap<String, HashSet<String>>,
        call_locations: &HashMap<(String, String), Location>,
    ) -> Option<Location> {
        for (calling_proc, called_procs) in call_graph {
            if called_procs.contains(procedure_name) {
                if let Some(location) =
                    call_locations.get(&(calling_proc.to_string(), procedure_name.to_string()))
                {
                    return Some(location.clone());
                }
            }
        }
        return None;
    }

    fn find_procedure_calls(&self, commands: &[Command]) -> HashSet<String> {
        let mut calls = HashSet::new();

        for command in commands {
            match command {
                Command::ProcedureCall { proc_name, .. } => {
                    calls.insert(proc_name.clone());
                }
                Command::IfElse {
                    then_commands,
                    else_commands,
                    ..
                } => {
                    calls.extend(self.find_procedure_calls(then_commands));
                    calls.extend(self.find_procedure_calls(else_commands));
                }
                Command::If { then_commands, .. } => {
                    calls.extend(self.find_procedure_calls(then_commands));
                }
                Command::While { commands, .. } => {
                    calls.extend(self.find_procedure_calls(commands));
                }
                Command::Repeat { commands, .. } => {
                    calls.extend(self.find_procedure_calls(commands));
                }
                Command::For { commands, .. } => {
                    calls.extend(self.find_procedure_calls(commands));
                }
                _ => {}
            }
        }

        return calls;
    }

    fn is_recursive(
        &self,
        call_graph: &HashMap<String, HashSet<String>>,
        procedure_name: &str,
        visited: &mut HashSet<String>,
    ) -> bool {
        if visited.contains(procedure_name) {
            return true;
        }

        visited.insert(procedure_name.to_string());

        if let Some(called_procedures) = call_graph.get(procedure_name) {
            for called_proc in called_procedures {
                if self.is_recursive(call_graph, called_proc, visited) {
                    return true;
                }
            }
        }

        visited.remove(procedure_name);
        return false;
    }
}
