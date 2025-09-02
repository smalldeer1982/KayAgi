import json

json_path = "temp_file_cea4619d-9906-4ad5-bec2-74f45b14aebd_tag_problems.json"

with open(json_path, "r", encoding="utf-8") as f:
    data = json.load(f)

# 输出所有一级节点（分类名）
for category in data.keys():
    print(category)