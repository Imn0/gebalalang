package tree_sitter_gbl_test

import (
	"testing"

	tree_sitter "github.com/tree-sitter/go-tree-sitter"
	tree_sitter_gbl "github.com/tree-sitter/tree-sitter-gbl/bindings/go"
)

func TestCanLoadGrammar(t *testing.T) {
	language := tree_sitter.NewLanguage(tree_sitter_gbl.Language())
	if language == nil {
		t.Errorf("Error loading Gbl grammar")
	}
}
