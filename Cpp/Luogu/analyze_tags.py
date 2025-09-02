import re
from collections import Counter

def analyze_problem_tags(file_path):
    """
    分析每个题目的标签处理情况
    """
    try:
        with open(file_path, "r", encoding="utf-8") as file:
            content = file.read()
            
            # 使用分隔符分割不同题目
            problems = content.split("\n---\n\n")
            
            # 需要排除的标签
            excluded_tags = [
                'USACO', 'O2优化', 'Special Judge', '福建省历届夏令营', '语言月赛', '洛谷月赛', '洛谷原创',
                'COCI', 'NOIP 普及组', '蓝桥杯省赛', 'ICPC', '江苏', '信息与未来', 'NOIP 提高组', 'CCC', 'ROIR',
                '传智杯', '蓝桥杯国赛', '梦熊比赛', '各省省选', '山东', 'PA', 'CSP-X 小学组', '高校校赛', 'NOI 导刊',
                '安徽', '分类讨论', 'CSP-J 入门级', '提交答案', 'XCPC', 'JOI', 'Ad-hoc', 'NOISG', 'CSP-S 提高级',
                'POI', '北京', '陕西', 'Code+', '广东', 'BalticOI', 'NOI Online', 'BCSP-X', '洛谷比赛', 'IOI',
                'NOI', '天津', '交互题', '\ufeff基础算法', '南京', '福建', '小学科创活动', '湖北', '湖南', '河南',
                '集训队互测', '吉林', '逆元', '云南', 'CEOI', '澳门', '济南', '上海', '青岛'
            ]
            
            analysis_results = []
            
            for problem in problems:
                if not problem.strip():
                    continue
                
                # 提取题目ID
                pid_match = re.search(r"pid:\s*(.+)", problem)
                pid = pid_match.group(1).strip() if pid_match else "未知ID"
                
                # 提取原始标签
                tag_match = re.search(r"tag:\s*\[(.*?)\]", problem)
                original_tags = []
                if tag_match:
                    raw_tags = tag_match.group(1)
                    original_tags = [t.strip().strip("'\"") for t in re.split(r",\s*", raw_tags)]
                
                # 过滤后的标签
                filtered_tags = [tag for tag in original_tags 
                               if tag not in excluded_tags 
                               and not tag.isdigit() 
                               and not (tag.startswith('20') and len(tag) == 4)]
                
                # 收集分析结果
                analysis_results.append({
                    "pid": pid,
                    "original_tags": original_tags,
                    "filtered_tags": filtered_tags,
                    "is_empty": len(filtered_tags) == 0
                })
            
            # 将结果写入文件
            output_path = r"d:\ChatgptKay\Luogu-Problem-main\tag_analysis.txt"
            with open(output_path, "w", encoding="utf-8") as out:
                out.write("题号\t原始标签\t处理后标签\t是否为空标签\n")
                for result in analysis_results:
                    out.write(f"{result['pid']}\t{', '.join(result['original_tags'])}\t{', '.join(result['filtered_tags'])}\t{'是' if result['is_empty'] else '否'}\n")
            
            print(f"✅ 分析结果已保存到 {output_path}")
            return analysis_results
            
    except Exception as e:
        print(f"❌ 错误：处理文件时出错 - {e}")
        return []