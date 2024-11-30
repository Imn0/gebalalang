import os


def get_all_dirs(path: str) -> list[str]:
    script_dir = os.path.dirname(os.path.abspath(__file__))
    full_path = os.path.join(script_dir, path)

    return [
        d for d in os.listdir(full_path) if os.path.isdir(os.path.join(full_path, d))
    ]


def get_all_files_in_dir(directory: str) -> list[str]:

    script_dir = os.path.dirname(os.path.abspath(__file__))
    full_path = os.path.join(script_dir, directory)

    file_paths: list[str] = []

    for root, _, files in os.walk(full_path):
        for file in files:
            file_path = os.path.join(root, file)
            file_paths.append(file_path)

    return file_paths
