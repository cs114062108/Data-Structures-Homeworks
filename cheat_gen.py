import os
import json
from pathlib import Path
import tkinter as tk
from tkinter import filedialog

base_path = Path(".")
cheat_sheet_dir = base_path / "cheat_sheets"

# [MAKEDIR] Try make cheat sheet dir if not exist
if not os.path.exists(cheat_sheet_dir):
    print("The directory does not exist, making it")
    cheat_sheet_dir.mkdir(parents=True, exist_ok=True)
    if not os.path.exists(cheat_sheet_dir):
        print("The directory does not exist")
    else:
        print("Successfully maked the directory")

root = tk.Tk()
root.withdraw()

try:
    title = input("Enter the title: ").strip() or "Title"

    file_names = []

    select_times = 10
    for i in range(select_times):
        select_file_names = filedialog.askopenfilenames(
            filetypes=[("C++ Source", ["*.cpp"])],
            initialdir=base_path
        )
        
        for file_name in select_file_names:
            if file_name not in file_names:
                file_names.append(file_name)
        
        file_names_text = json.dumps(file_names, indent=2, ensure_ascii=False)
        print(f"Selected source files:\n{file_names_text}")
        if i < select_times-1:
            more = input("More sources? (y/n): ").strip().lower() == "y"
            if not more:
                break


    if not file_names:
        exit(0)

    markdown_text = f"# {title}" + "\n\n"
    MD_PAGE_BREAKER = """<div style="page-break-after: always;"></div>"""

    for file_name in file_names:
        code_text = ""
        code = ""
        source_name = Path(file_name).name
        with open(file_name, "r", encoding="utf-8") as f:
            code = f.read()
            code_text = f"```cpp\n{code}\n```" + "\n"
        markdown_text += f"### `{source_name}`\n" + code_text + f"\n{MD_PAGE_BREAKER}\n\n"

    markdown_filename = filedialog.asksaveasfilename(
        filetypes=[("Cheatsheet Markdown", ["*.md"])],
        initialdir=cheat_sheet_dir
    ).strip()
    print(f"Markdown filename to save: {markdown_filename}")

    if markdown_filename:
        if not markdown_filename.endswith(".md"):
            markdown_filename += ".md"
        with open(markdown_filename, "w", encoding="utf-8") as f:
            f.write(markdown_text)
except KeyboardInterrupt:
    print("Bye~~")
