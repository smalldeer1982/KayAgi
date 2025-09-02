import json
import urllib.request
import requests
import bs4 as bs
import re
import os
import time


# 难度映射表
difficulty_mapping = {
    1: "入门",
    2: "普及-",
    3: "普及/提高-",
    4: "普及+/提高",
    5: "提高+/省选-",
    6: "省选/NOI-",
    7: "NOI/NOI+/CTSC"
}

# 标签映射表 - 从tag_mapping_result.json生成
tag_mapping = {
    1: "模拟",
    2: "字符串",
    3: "动态规划 DP",
    4: "搜索",
    5: "数学",
    6: "图论",
    7: "贪心",
    8: "计算几何",
    9: "暴力数据结构",
    10: "高精度",
    11: "树形数据结构",
    12: "递推",
    13: "博弈论",
    14: "1997",
    15: "1998",
    16: "1999",
    17: "2000",
    18: "2001",
    19: "2002",
    20: "2003",
    21: "2004",
    22: "2005",
    23: "2006",
    24: "2007",
    25: "2008",
    26: "2009",
    27: "2010",
    28: "2011",
    29: "2012",
    30: "2013",
    31: "2014",
    32: "2015",
    33: "2016",
    34: "2017",
    35: "2018",
    36: "2019",
    37: "2020",
    38: "重庆",
    39: "四川",
    40: "河南",
    41: "莫队",
    42: "线段树",
    43: "倍增",
    44: "线性数据结构",
    45: "二分",
    46: "USACO",
    47: "并查集",
    48: "各省省选",
    49: "点分治",
    50: "平衡树",
    51: "堆",
    52: "集训队互测",
    53: "树状数组",
    54: "递归",
    55: "树上启发式合并",
    56: "单调队列",
    57: "POI（波兰）",
    58: "2021",
    59: "2022",
    60: "2023",
    61: "2024",
    62: "2025",
    63: "LGV 引理",
    64: "矩阵树定理",
    65: "颜色段均摊（珂朵莉树 ODT）",
    66: "原根",
    67: "三分",
    68: "Kruskal 重构树",
    69: "多项式",
    70: "福建省历届夏令营",
    71: "矩阵运算",
    72: "数论",
    73: "未知标签73",
    74: "数据结构",
    75: "未知标签75",
    76: "未知标签76",
    77: "NOI",
    78: "离散化",
    79: "网络流",
    80: "高级数据结构",
    81: "洛谷原创",
    82: "NOIP 普及组",
    83: "NOIP 提高组",
    84: "未知标签84",
    85: "APIO",
    86: "未知标签86",
    87: "未知标签87",
    88: "浙江",
    89: "上海",
    90: "福建",
    91: "江苏",
    92: "安徽",
    93: "湖南",
    94: "北京",
    95: "河北",
    96: "广东",
    97: "山东",
    98: "吉林",
    99: "NOI 导刊",
    100: "cdq 分治",
    101: "后缀自动机 SAM",
    102: "IOI",
    103: "交互题",
    104: "提交答案",
    105: "未知标签105",
    106: "未知标签106",
    107: "Special Judge",
    108: "O2优化",
    109: "未知标签109",
    110: "\\ufeff基础算法",
    111: "枚举",
    112: "分治",
    113: "排序",
    114: "各省省选",
    115: "CCO（加拿大）",
    116: "CCC（加拿大）",
    117: "CEOI（中欧）",
    118: "eJOI（欧洲）",
    119: "未知标签119",
    120: "未知标签120",
    121: "未知标签121",
    122: "交互题",
    123: "未知标签123",
    124: "未知标签124",
    125: "未知标签125",
    126: "广度优先搜索 BFS",
    127: "深度优先搜索 DFS",
    128: "剪枝",
    129: "记忆化搜索",
    130: "搜索",
    131: "搜索",
    132: "启发式迭代加深搜索 IDA*",
    133: "Dancing Links",
    134: "动态规划 DP",
    135: "模拟退火",
    136: "随机调整",
    137: "洛谷原创",
    138: "未知标签138",
    139: "背包 DP",
    140: "未知标签140",
    141: "数位 DP",
    142: "未知标签142",
    143: "未知标签143",
    144: "区间 DP",
    145: "未知标签145",
    146: "动态规划优化",
    147: "未知标签147",
    148: "优先队列",
    149: "矩阵加速",
    150: "斜率优化",
    151: "状态合并",
    152: "树形 DP",
    153: "凸完全单调性（wqs 二分）",
    154: "四边形不等式",
    155: "图论建模",
    156: "未知标签156",
    157: "2014",
    158: "图遍历",
    159: "拓扑排序",
    160: "最短路",
    161: "未知标签161",
    162: "各省省选",
    163: "广西",
    164: "陕西",
    165: "未知标签165",
    166: "生成树",
    167: "各省省选",
    168: "2019",
    169: "2016",
    170: "未知标签170",
    171: "2016",
    172: "平面图",
    173: "最小环",
    174: "负权环",
    175: "连通块",
    176: "2-SAT",
    177: "平面图欧拉公式",
    178: "未知标签178",
    179: "强连通分量",
    180: "Tarjan",
    181: "双连通分量",
    182: "欧拉回路",
    183: "未知标签183",
    184: "未知标签184",
    185: "差分约束",
    186: "仙人掌",
    187: "二分图",
    188: "未知标签188",
    189: "Special Judge",
    190: "未知标签190",
    191: "未知标签191",
    192: "Special Judge",
    193: "未知标签193",
    194: "未知标签194",
    195: "未知标签195",
    196: "未知标签196",
    197: "上下界网络流",
    198: "最小割",
    199: "未知标签199",
    200: "未知标签200",
    201: "未知标签201",
    202: "分数规划",
    203: "未知标签203",
    204: "费用流",
    205: "未知标签205",
    206: "未知标签206",
    207: "未知标签207",
    208: "树的遍历",
    209: "数学",
    210: "未知标签210",
    211: "最近公共祖先 LCA",
    212: "未知标签212",
    213: "树的直径",
    214: "2015",
    215: "可并堆",
    216: "未知标签216",
    217: "未知标签217",
    218: "未知标签218",
    219: "未知标签219",
    220: "未知标签220",
    221: "未知标签221",
    222: "未知标签222",
    223: "未知标签223",
    224: "未知标签224",
    225: "未知标签225",
    226: "未知标签226",
    227: "未知标签227",
    228: "树链剖分",
    229: "动态树 LCT",
    230: "树论",
    231: "未知标签231",
    232: "树套树",
    233: "可持久化线段树",
    234: "可持久化",
    235: "哈希 hashing",
    236: "未知标签236",
    237: "未知标签237",
    238: "未知标签238",
    239: "素数判断,质数,筛法",
    240: "未知标签240",
    241: "最大公约数 gcd",
    242: "扩展欧几里德算法",
    243: "不定方程",
    244: "进制",
    245: "未知标签245",
    246: "群论",
    247: "置换",
    248: "Pólya 定理",
    249: "虚树",
    250: "中国剩余定理 CRT",
    251: "莫比乌斯反演",
    252: "组合数学",
    253: "排列组合",
    254: "前缀和",
    255: "二项式定理",
    256: "康托展开",
    257: "未知标签257",
    258: "鸽笼原理",
    259: "容斥原理",
    260: "斐波那契数列",
    261: "Catalan 数",
    262: "Stirling 数",
    263: "A*  算法",
    264: "生成函数",
    265: "线性规划",
    266: "概率论",
    267: "未知标签267",
    268: "条件概率",
    269: "未知标签269",
    270: "期望",
    271: "线性代数",
    272: "矩阵乘法",
    273: "线性递推",
    274: "高斯消元",
    275: "未知标签275",
    276: "逆元",
    277: "线性基",
    278: "微积分",
    279: "未知标签279",
    280: "导数",
    281: "积分",
    282: "数学",
    283: "计算几何",
    284: "级数",
    285: "未知标签285",
    286: "向量",
    287: "栈",
    288: "队列",
    289: "分块",
    290: "ST 表",
    291: "凸包",
    292: "叉积",
    293: "线段相交",
    294: "未知标签294",
    295: "半平面交",
    296: "未知标签296",
    297: "未知标签297",
    298: "扫描线",
    299: "凸包",
    300: "字典树 Trie",
    301: "AC 自动机",
    302: "KMP 算法",
    303: "后缀数组 SA",
    304: "后缀树",
    305: "有限状态自动机",
    306: "未知标签306",
    307: "未知标签307",
    308: "其它技巧",
    309: "随机化",
    310: "未知标签310",
    311: "博弈树",
    312: "未知标签312",
    313: "快速傅里叶变换 FFT",
    314: "位运算",
    315: "未知标签315",
    316: "整体二分",
    317: "未知标签317",
    318: "构造",
    319: "未知标签319",
    320: "基环树",
    321: "K-D Tree",
    322: "Lucas 定理",
    323: "插头 DP",
    324: "快速数论变换 NTT",
    325: "回文自动机 PAM",
    326: "快速沃尔什变换 FWT",
    327: "快速沃尔什变换 FWT",
    328: "天津",
    329: "Manacher 算法",
    330: "差分",
    331: "CTT（清华集训/北大集训）",
    332: "网络流与线性规划 24 题",
    333: "COCI（克罗地亚）",
    334: "BalticOI（波罗的海）",
    335: "ICPC",
    336: "JOI（日本）",
    337: "洛谷月赛",
    338: "未知标签338",
    339: "未知标签339",
    340: "未知标签340",
    341: "O2优化",
    342: "CSP-S 提高级",
    343: "CSP-J 入门级",
    344: "1996",
    345: "双指针 two-pointer",
    346: "O2优化",
    347: "NOI Online",
    348: "O2优化",
    349: "未知标签349",
    350: "圆方树",
    351: "Special Judge",
    352: "未知标签352",
    353: "顺序结构",
    354: "分支结构",
    355: "循环结构",
    356: "数组",
    357: "字符串（入门）",
    358: "结构体",
    359: "函数与递归",
    360: "链表",
    361: "蓝桥杯国赛",
    362: "O2优化",
    363: "蓝桥杯省赛",
    364: "数学",
    365: "Ad-hoc",
    366: "未知标签366",
    367: "图论",
    368: "笛卡尔树",
    369: "未知标签369",
    370: "博弈论",
    371: "根号分治",
    372: "O2优化",
    373: "模拟费用流",
    374: "二分",
    375: "均摊分析",
    376: "分类讨论",
    377: "李超线段树",
    378: "吉司机线段树 segment tree beats",
    379: "线段树合并",
    380: "折半搜索 meet in the middle",
    381: "XCPC",
    382: "O2优化",
    383: "传智杯",
    384: "未知标签384",
    385: "单调栈",
    386: "语言月赛",
    387: "杨表",
    388: "类欧几里得算法",
    389: "PA（波兰）",
    390: "THUPC",
    391: "Berlekamp-Massey(BM) 算法",
    392: "未知标签392",
    393: "ROI（俄罗斯）",
    394: "O2优化",
    395: "未知标签395",
    396: "未知标签396",
    397: "O2优化",
    398: "未知标签398",
    399: "未知标签399",
    400: "未知标签400",
    401: "未知标签401",
    402: "未知标签402",
    403: "未知标签403",
    404: "未知标签404",
    405: "未知标签405",
    406: "未知标签406",
    407: "未知标签407",
    408: "2021",
    409: "GESP",
    410: "Prüfer 序列",
    411: "数学",
    412: "数学",
    413: "未知标签413",
    414: "未知标签414",
    415: "O2优化",
    416: "快速沃尔什变换 FWT",
    417: "拉格朗日插值法",
    418: "未知标签418",
    419: "字符串",
    420: "2022",
    421: "O2优化",
    422: "2018",
    423: "Stern-Brocot 树",
    424: "O2优化",
    425: "未知标签425",
    426: "未知标签426",
    427: "未知标签427",
    428: "未知标签428",
    429: "洛谷比赛",
    430: "未知标签430",
    431: "未知标签431",
    432: "THUSC",
    433: "未知标签433",
    434: "高校校赛",
    435: "DP 套 DP",
    436: "NOISG（新加坡）",
    437: "NordicOI（北欧）",
    438: "THUWC",
    439: "BalkanOI（巴尔干半岛）",
    440: "交互题",
    441: "RMI（罗马尼亚）",
    442: "山东",
    443: "动态 DP",
    444: "动态规划 DP",
    445: "SG 函数",
    446: "线段树分治",
    447: "离线处理",
    448: "整除分块",
    449: "USACO",
    450: "弦图"
}


def json_parser(html: str):
    try:
        soup = bs.BeautifulSoup(html, "html.parser")
        
        # 首先尝试查找 id 为 lentille-context 的 script 标签
        script = soup.find('script', id='lentille-context')
        
        if script:
            # 提取 script 标签中的 JSON 数据
            json_str = script.string.strip()
            data = json.loads(json_str)
            return data
        else:
            # 尝试查找包含 window._feInjection 的脚本
            scripts = soup.find_all('script')
            for script in scripts:
                if script.string and 'window._feInjection' in script.string:
                    # 提取 JSON 数据
                    json_str = script.string.strip()
                    # 提取 JSON 部分
                    json_start = json_str.find('window._feInjection = JSON.parse(decodeURIComponent("')
                    if json_start != -1:
                        json_start += len('window._feInjection = JSON.parse(decodeURIComponent("')
                        json_end = json_str.find('"))', json_start)
                        if json_end != -1:
                            encoded_json = json_str[json_start:json_end]
                            # 解码 URL 编码的 JSON 字符串
                            decoded_json = urllib.parse.unquote(encoded_json)
                            data = json.loads(decoded_json)
                            return data
            
            return None
    except Exception as e:
        print(f"JSON解析错误: {str(e)}")
        return None

def sanitize_filename(filename):
    """清理文件名，移除非法字符"""
    # 替换Windows文件系统中不允许的字符
    invalid_chars = r'<>:"/\|?*'
    for char in invalid_chars:
        filename = filename.replace(char, '_')
    
    # 替换其他可能导致问题的字符
    filename = filename.replace('\n', ' ').replace('\r', ' ')
    
    # 限制文件名长度
    if len(filename) > 200:
        filename = filename[:197] + '...'
    
    return filename

def problem_markdown_parser(problem_js: dict, difficulty="未知", tags=None):
    """将题目数据转换为Markdown格式，添加YAML前置信息"""
    try:
        pid = problem_js["pid"]
        title = problem_js["title"]
        
        # 清理文件名
        safe_title = sanitize_filename(title)
        filename = f"{pid}-{safe_title}.md"
        
        # 检查content是否存在
        content = {}
        if "content" in problem_js and problem_js["content"] is not None:
            content = problem_js["content"]
        elif "contenu" in problem_js and problem_js["contenu"] is not None:
            content = problem_js["contenu"]
        
        print(f"处理题目: {pid} - {title}")
        print(f"内容类型: {type(content)}")
        print(f"内容键: {list(content.keys()) if isinstance(content, dict) else 'None'}")
        
        if tags is None:
            tags = []
        
        # 创建Markdown文件
        with open(filename, "w", encoding="utf-8") as f:
            # 写入YAML前置信息
            f.write("---\n")
            f.write(f'title: "{title}"\n')
            f.write('layout: "post"\n')
            f.write(f'diff: {difficulty}\n')
            f.write(f'pid: {pid}\n')
            f.write(f'tag: {tags}\n')
            f.write("---\n\n")
            
            # 写入题目部分
            f.write(f"# {title}\n\n")
            
            # 写入背景
            if isinstance(content, dict) and content.get("background"):
                f.write("## 题目背景\n\n")
                f.write(f"{content['background']}\n\n")
                
            # 写入描述
            if isinstance(content, dict) and content.get("description"):
                f.write("## 题目描述\n\n")
                f.write(f"{content['description']}\n\n")
                
            # 写入输入格式
            if isinstance(content, dict) and content.get("inputFormat") or content.get("formatI"):
                f.write("## 输入格式\n\n")
                input_format = content.get("inputFormat") or content.get("formatI")
                f.write(f"{input_format}\n\n")
                
            # 写入输出格式
            if isinstance(content, dict) and content.get("outputFormat") or content.get("formatO"):
                f.write("## 输出格式\n\n")
                output_format = content.get("outputFormat") or content.get("formatO")
                f.write(f"{output_format}\n\n")
                
            # 写入提示
            if isinstance(content, dict) and content.get("hint"):
                f.write("## 说明/提示\n\n")
                f.write(f"{content['hint']}\n\n")
                
            # 写入样例
            if "samples" in problem_js and problem_js["samples"]:
                for i, sample in enumerate(problem_js["samples"], 1):
                    f.write(f"## 样例 #{i}\n\n")
                    f.write("### 输入\n\n")
                    f.write("```\n")
                    f.write(f"{sample[0]}")
                    f.write("\n```\n\n")
                    f.write("### 输出\n\n")
                    f.write("```\n")
                    f.write(f"{sample[1]}")
                    f.write("\n```\n\n")
            
            # 如果没有内容，添加一个提示
            if not isinstance(content, dict) or not content:
                f.write("## 题目内容\n\n")
                f.write("*此题目内容不可用或格式不兼容*\n\n")
                f.write("请访问原题链接: " + f"https://www.luogu.com.cn/problem/{pid}\n\n")
                    
        print(f"成功生成题目Markdown文件: {filename}")
                
    except Exception as e:
        print(f"Markdown转换错误: {str(e)}")
        print(f"错误类型: {type(e)}")
        
        # 尝试创建一个最小的Markdown文件
        try:
            pid = problem_js.get("pid", "unknown")
            title = problem_js.get("title", "未知题目")
            safe_title = sanitize_filename(title)
            filename = f"{pid}-{safe_title}.md"
            
            with open(filename, "w", encoding="utf-8") as f:
                f.write("---\n")
                f.write(f'title: "{title}"\n')
                f.write('layout: "post"\n')
                f.write(f'diff: {difficulty}\n')
                f.write(f'pid: {pid}\n')
                f.write(f'tag: {tags if tags else []}\n')
                f.write("---\n\n")
                
                f.write(f"# {title}\n\n")
                f.write("## 题目内容\n\n")
                f.write("*此题目内容不可用或格式不兼容*\n\n")
                f.write("请访问原题链接: " + f"https://www.luogu.com.cn/problem/{pid}\n\n")
                
            print(f"已创建最小Markdown文件: {filename}")
        except Exception as inner_e:
            print(f"创建最小Markdown文件失败: {str(inner_e)}")

def pid_parser(pid: str):
    """解析单个题目的详细信息"""
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36',
    }
    problem_url = "https://www.luogu.com.cn/problem/"

    try:
        # 获取题目内容
        problem_rsp = requests.get(problem_url + pid, headers=headers)
        print(f"题目请求状态码: {problem_rsp.status_code}")
        
        # 保存原始HTML响应到日志文件
        log_dir = "logs"
        os.makedirs(log_dir, exist_ok=True)
        with open(f"{log_dir}/{pid}_response.html", "w", encoding="utf-8") as f:
            f.write(problem_rsp.text)
        
        # 使用 json_parser 处理HTML响应
        problem_data = json_parser(problem_rsp.text)
        
        # 保存JSON数据到日志文件
        if problem_data:
            with open(f"{log_dir}/{pid}_data.json", "w", encoding="utf-8") as f:
                json.dump(problem_data, f, indent=4, ensure_ascii=False)
        
        if not problem_data:
            print("题目数据为空")
            return
        
        # 从JSON中提取题目数据
        if "data" not in problem_data or "problem" not in problem_data["data"]:
            print("题目数据格式错误")
            return
            
        problem_js = problem_data["data"]["problem"]
        
        # 提取题目内容
        content = None
        if "contenu" in problem_js and problem_js["contenu"]:
            content = problem_js["contenu"]
        elif "content" in problem_js and problem_js["content"]:
            content = problem_js["content"]
        
        # 提取标签和难度
        tags = []
        difficulty = "未知"
        
        if "tags" in problem_js:
            tag_ids = problem_js["tags"]
            tags = [tag_mapping.get(tag_id, f"标签{tag_id}") for tag_id in tag_ids]
        
        if "difficulty" in problem_js:
            diff_id = problem_js["difficulty"]
            difficulty = difficulty_mapping.get(diff_id, f"难度{diff_id}")
        
        print(f"题目信息: {pid} - {problem_js['title']}")
        print(f"难度: {difficulty}")
        print(f"标签: {tags}")
        
        # 构建完整的题目数据
        problem_data = {
            "pid": problem_js["pid"],
            "title": problem_js["title"],
            "difficulty": difficulty,
            "tags": tags,
            "content": content,
            "samples": problem_js.get("samples", [])
        }
        
        # 将题目数据转换为Markdown
        problem_markdown_parser(problem_data, difficulty, tags)
        
        return problem_data
    
    except Exception as e:
        print(f"处理题目 {pid} 时出错: {str(e)}")
        print(f"错误类型: {type(e)}")
        import traceback
        traceback.print_exc()
        return None

def parse_problem_list(problem_type="CF", start_page=1, max_pages=None):
    """
    解析题目列表页面，获取题目ID
    
    Args:
        problem_type: 题目类型，如 CF（CodeForces）
        start_page: 起始页码
        max_pages: 最大页数，None表示爬取所有页
    
    Returns:
        题目ID列表
    """
    base_url = f"https://www.luogu.com.cn/problem/list?type={problem_type}"
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36',
    }
    
    all_problem_ids = []
    current_page = start_page
    
    while True:
        page_url = f"{base_url}&page={current_page}"
        print(f"\n=== 获取第 {current_page} 页题目列表 ===")
        print(f"请求URL: {page_url}")
        
        try:
            response = requests.get(page_url, headers=headers)
            print(f"状态码: {response.status_code}")
            
            # 解析HTML获取题目列表
            soup = bs.BeautifulSoup(response.text, "html.parser")
            
            # 尝试获取JSON数据
            json_data = json_parser(response.text)
            if json_data:
                # 从JSON数据中提取题目信息
                if "currentData" in json_data and "problems" in json_data["currentData"]:
                    problems_data = json_data["currentData"]["problems"]
                    
                    # 提取题目列表
                    for problem in problems_data.get("result", []):
                        problem_id = problem.get("pid", "")
                        if problem_id:
                            all_problem_ids.append(problem_id)
                            print(f"从JSON找到题目ID: {problem_id}")
                    
                    # 检查是否有下一页
                    if len(problems_data.get("result", [])) < 50 or (max_pages and current_page >= max_pages):
                        print("已到达最后一页或达到最大页数限制")
                        break
                    
                    current_page += 1
                    time.sleep(1)  # 避免请求过于频繁
                    continue
            
            # 如果JSON解析失败，尝试从HTML中提取
            problem_items = soup.select('a[href^="/problem/"]')
            page_problem_ids = []
            
            for item in problem_items:
                try:
                    href = item.get('href')
                    if href and '/problem/' in href:
                        problem_id = href.split('/problem/')[1]
                        if problem_id and problem_id not in page_problem_ids:
                            page_problem_ids.append(problem_id)
                            print(f"从HTML找到题目ID: {problem_id}")
                except Exception as e:
                    print(f"处理题目项时出错: {str(e)}")
            
            if page_problem_ids:
                all_problem_ids.extend(page_problem_ids)
            else:
                print("本页未找到题目ID")
                break
            
            # 检查是否有下一页
            next_page = soup.select_one('a.page-link[aria-label="Next"]')
            if not next_page or (max_pages and current_page >= max_pages):
                print("已到达最后一页或达到最大页数限制")
                break
            
            current_page += 1
            time.sleep(1)  # 避免请求过于频繁
            
        except Exception as e:
            print(f"处理第 {current_page} 页时出错: {str(e)}")
            break
    
    # 去重
    all_problem_ids = list(dict.fromkeys(all_problem_ids))
    print(f"\n总共找到 {len(all_problem_ids)} 个题目ID")
    
    return all_problem_ids

def process_problem_list(problem_type="AT", start_page=1, max_pages=None, max_problems=None):
    """
    处理题目列表，获取详细信息
    
    Args:
        problem_type: 题目类型
        start_page: 起始页码
        max_pages: 最大页数
        max_problems: 最大题目数量
    """
    # 获取当前脚本所在目录
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    # 创建输出目录 (AT/problems_AT)
    output_dir = os.path.join(script_dir, f"problems_{problem_type}")
    os.makedirs(output_dir, exist_ok=True)
    
    # 切换到输出目录
    current_dir = os.getcwd()
    os.chdir(output_dir)
    
    try:
        # 获取题目ID列表
        problem_ids = parse_problem_list(problem_type, start_page, max_pages)
        
        if max_problems:
            problem_ids = problem_ids[:max_problems]
        
        # 批次处理变量
        batch_count = 0
        batch_start_time = time.time()
        
        # 处理每个题目
        for i, pid in enumerate(problem_ids, 1):
            print(f"\n处理第 {i}/{len(problem_ids)} 个题目: {pid}")
            
            try:
                pid_parser(pid)
                batch_count += 1
                
                # 检查是否需要休息
                current_time = time.time()
                time_elapsed = current_time - batch_start_time
                
                if batch_count >= 5 or time_elapsed >= 20:
                    print(f"\n=== 已处理 {batch_count} 题，耗时 {time_elapsed:.2f} 秒 ===")
                    print("休息5秒...")
                    time.sleep(5)
                    batch_count = 0
                    batch_start_time = time.time()
            except Exception as e:
                print(f"处理题目 {pid} 时出错: {str(e)}")
    
    except Exception as e:
        print(f"处理题目列表时出错: {str(e)}")
    
    finally:
        # 恢复原始目录
        os.chdir(current_dir)

def parse_tag_info(tag_id=None, max_pages=1):
    """
    解析特定标签的题目列表，获取标签信息和题目
    
    Args:
        tag_id: 标签ID，如4表示动态规划
        max_pages: 最大页数
    
    Returns:
        题目列表和标签信息
    """
    if tag_id is None:
        base_url = "https://www.luogu.com.cn/problem/list"
    else:
        base_url = f"https://www.luogu.com.cn/problem/list?tag={tag_id}"
    
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/116.0.0.0 Safari/537.36',
    }
    
    all_problems = []
    tag_name = f"标签{tag_id}" if tag_id else "全部"
    
    # 创建日志目录
    log_dir = "html_logs"
    os.makedirs(log_dir, exist_ok=True)
    
    for page in range(1, max_pages + 1):
        page_url = f"{base_url}&page={page}" if tag_id else f"{base_url}?page={page}"
        print(f"\n=== 获取标签 {tag_id} 第 {page} 页题目列表 ===")
        print(f"请求URL: {page_url}")
        
        try:
            response = requests.get(page_url, headers=headers)
            print(f"状态码: {response.status_code}")
            
            # 保存原始HTML响应到文件
            html_filename = f"{log_dir}/tag_{tag_id}_page_{page}.html"
            with open(html_filename, "w", encoding="utf-8") as f:
                f.write(response.text)
            print(f"已保存HTML响应到: {html_filename}")
            
            # 解析HTML获取题目列表
            soup = bs.BeautifulSoup(response.text, "html.parser")
            
            # 尝试获取标签名称
            tag_header = soup.select_one('h1.lfe-h1')
            if tag_header:
                header_text = tag_header.text.strip()
                if '：' in header_text:
                    tag_name = header_text.split('：')[1].strip()
                    print(f"找到标签名称: {tag_name}")
            
            # 尝试获取JSON数据
            json_data = json_parser(response.text)
            
            # 保存解析后的JSON数据
            if json_data:
                json_filename = f"{log_dir}/tag_{tag_id}_page_{page}_data.json"
                with open(json_filename, "w", encoding="utf-8") as f:
                    json.dump(json_data, f, indent=4, ensure_ascii=False)
                print(f"已保存JSON数据到: {json_filename}")
            
            if json_data and "currentData" in json_data:
                # 从JSON数据中提取标签信息
                if "tagMap" in json_data["currentData"]:
                    tag_map = json_data["currentData"]["tagMap"]
                    for tag_key, tag_value in tag_map.items():
                        print(f"标签ID: {tag_key}, 标签名称: {tag_value}")
                
                # 从JSON数据中提取题目信息
                if "problems" in json_data["currentData"]:
                    problems_data = json_data["currentData"]["problems"]
                    
                    # 提取题目列表
                    for problem in problems_data.get("result", []):
                        problem_id = problem.get("pid", "")
                        title = problem.get("title", "")
                        difficulty = problem.get("difficulty", 0)
                        
                        if problem_id:
                            problem_info = {
                                "id": problem_id,
                                "title": title,
                                "difficulty": difficulty_mapping.get(difficulty, "未知"),
                                "tags": [tag_name] if tag_id else []
                            }
                            all_problems.append(problem_info)
                            print(f"从JSON找到题目: {problem_id} - {title}")
            
            # 如果JSON解析失败，尝试从HTML中提取
            if not all_problems:
                problem_items = soup.select('.lg-table-row')
                for item in problem_items:
                    try:
                        problem_id = item.select_one('.pid').text.strip()
                        title = item.select_one('.title').text.strip()
                        
                        problem_info = {
                            "id": problem_id,
                            "title": title,
                            "difficulty": "未知",
                            "tags": [tag_name] if tag_id else []
                        }
                        
                        all_problems.append(problem_info)
                        print(f"从HTML找到题目: {problem_id} - {title}")
                    except Exception as e:
                        print(f"处理题目项时出错: {str(e)}")
            
            # 检查是否有下一页
            if page >= max_pages:
                print(f"已达到最大页数限制: {max_pages}")
                break
                
        except Exception as e:
            print(f"处理标签 {tag_id} 第 {page} 页时出错: {str(e)}")
            break
    
    print(f"\n总共找到 {len(all_problems)} 个题目")
    
    # 保存所有题目信息到文件
    with open(f"tag_{tag_id}_problems.json", "w", encoding="utf-8") as f:
        json.dump(all_problems, f, indent=4, ensure_ascii=False)
    
    return all_problems, tag_name

def extract_tag_mapping():
    """
    提取所有标签的映射关系
    """
    tag_mapping = {}
    
    # 尝试访问不同标签的页面
    for tag_id in range(1, 100):  # 假设标签ID从1到99
        try:
            _, tag_name = parse_tag_info(tag_id, max_pages=1)
            if tag_name and tag_name != f"标签{tag_id}":
                tag_mapping[tag_id] = tag_name
                print(f"找到标签映射: {tag_id} -> {tag_name}")
                time.sleep(1)  # 避免请求过于频繁
        except Exception as e:
            print(f"处理标签 {tag_id} 时出错: {str(e)}")
    
    # 保存标签映射到文件
    with open("tag_mapping.json", "w", encoding="utf-8") as f:
        json.dump(tag_mapping, f, indent=4, ensure_ascii=False)
    
    return tag_mapping

if __name__ == "__main__":
    # 处理CF题目列表，从第1页开始，最多处理5页
    process_problem_list(problem_type="SP", start_page=1, max_pages=74)
