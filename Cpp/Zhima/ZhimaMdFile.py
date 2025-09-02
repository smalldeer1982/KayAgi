import os
import json

def extract_json_to_md(folder_path, output_md_file):
    """
    Extracts content from JSON files in a folder and writes to a Markdown file.

    Args:
    - folder_path: The folder containing JSON files.
    - output_md_file: The Markdown output file path.
    """
    # Ensure the output directory exists
    output_dir = os.path.dirname(output_md_file)
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    with open(output_md_file, 'w', encoding='utf-8') as md_file:
        # Iterate through all files in the folder
        for file_name in sorted(os.listdir(folder_path)):
            # Check if the file is a JSON file
            if file_name.endswith('.json'):
                file_path = os.path.join(folder_path, file_name)
                with open(file_path, 'r', encoding='utf-8') as json_file:
                    try:
                        data = json.load(json_file)

                        # Extract fields or use defaults
                        title = data.get('title', '未命名题目')
                        problem_info = data.get('problem_info', '无题目描述').replace('\\n', '\n')
                        submission_code = data.get('submission_code', '// 无代码提供')

                        # Write content to Markdown file
                        md_file.write(f"# {title}\n\n")
                        md_file.write(f"## 题目描述\n\n{problem_info}\n\n")
                        md_file.write(f"### 代码\n\n```cpp\n{submission_code}\n```\n\n")
                        md_file.write(f"---\n\n")
                    except json.JSONDecodeError:
                        print(f"Error decoding JSON file: {file_name}")
                        continue

# Folder containing the JSON files
folder_path = 'output_zhima'

# Output Markdown file
output_md_file = 'output_zhima_mdfile/submitcode_zhima0303.md'

# Run the function
extract_json_to_md(folder_path, output_md_file)

print(f"Markdown file '{output_md_file}' has been created.")
