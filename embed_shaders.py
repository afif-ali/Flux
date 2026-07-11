from pathlib import Path
import shutil
import sys

shader_dir = Path(sys.argv[1])
output_dir = Path(sys.argv[2])

if output_dir.exists():
    shutil.rmtree(output_dir)

output_dir.mkdir(parents=True, exist_ok=True)


def make_variable_name(path: Path):
    return (
        path.stem.replace(".", "_")
                 .replace("-", "_")
                 .replace(" ", "_")
                 .upper()
        + "_"
        + path.suffix[1:].upper()
    )


for shader in shader_dir.rglob("*"):

    if not shader.is_file():
        continue

    variable = make_variable_name(shader)

    output = output_dir / (shader.name + ".hpp")

    with open(output, "w", encoding="utf8") as f:

        f.write("#pragma once\n\n")

        f.write(f"constexpr const char* {variable} = R\"SHADER(\n")

        f.write(shader.read_text())

        f.write("\n)SHADER\";\n")

(output_dir / "shaders.stamp").touch()