# 题目信息

# Chat Order

## 题目描述

有一个队列，初始时为空。现在依次插入 $n$ 个单词，如果这个单词已经在队列中，那就把这个单词从原来位置移到队首，否则直接把这个单词放到队首。问你最后这个队列长啥样。

## 样例 #1

### 输入

```
4
alex
ivan
roman
ivan
```

### 输出

```
ivan
roman
alex
```

## 样例 #2

### 输入

```
8
alina
maria
ekaterina
darya
darya
ekaterina
maria
alina
```

### 输出

```
alina
maria
ekaterina
darya
```

# AI分析结果

### 题目内容（已为中文，无需翻译）
有一个队列，初始时为空。现在依次插入 $n$ 个单词，如果这个单词已经在队列中，那就把这个单词从原来位置移到队首，否则直接把这个单词放到队首。问你最后这个队列长啥样。

### 综合分析与结论
- **思路对比**：
    - Michael123456和happybob思路一致，反向遍历记录单词是否输出，避免了正向操作的移动处理。
    - 反手一只MJJ使用栈存储单词，先全部入栈再边输出边判重。
    - UperFicial使用双向链表，先将单词插入队尾再去重，最后反着输出。
    - Eason_AC用结构体存储单词和最后出现位置，按位置排序输出。
- **算法要点**：
    - 前两者主要利用 `map` 判重，结合反向遍历或栈操作。
    - UperFicial利用双向链表的插入删除特性。
    - Eason_AC用 `map` 映射结合结构体排序。
- **解决难点**：
    - 都解决了单词判重和移动到队首的问题。前两者通过反向思维简化操作，UperFicial用链表优化插入删除，Eason_AC用排序解决顺序问题。

### 所选题解
- **Michael123456（5星）**：
    - **关键亮点**：思路清晰，反向思考简化问题，代码简洁易读，时间复杂度低。
    - **核心代码**：
```cpp
map<string,bool>mp;
int n;
string s[200000+10];

int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>s[i];
    for(int i=n;i>=1;i--)
    {
        if(mp[s[i]])continue;
        cout<<s[i]<<'\n';
        mp[s[i]]=true;
    }
    return 0;
} 
```
核心思想：反向遍历单词数组，用 `map` 记录单词是否已输出，未输出则输出并标记。

- **Eason_AC（4星）**：
    - **关键亮点**：利用结构体存储单词和最后出现位置，通过排序解决最终队列顺序问题。
    - **核心代码**：
```cpp
struct node {
    string name;
    int last;
    bool operator < (const node& cjy) const {return last > cjy.last;}
}a[200007];
map<string, int> vis;
int n, cnt;

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        string s;
        cin >> s;
        if(!vis[s]) {
            a[++cnt].name = s;
            vis[s] = cnt;
        }
        a[vis[s]].last = i;
    }
    sort(a + 1, a + cnt + 1);
    for(int i = 1; i <= cnt; ++i)
        cout << a[i].name << endl;
    return 0;
}
```
核心思想：用结构体存储单词和最后出现位置，用 `map` 记录单词对应的结构体下标，最后按位置排序输出。

- **happybob（4星）**：
    - **关键亮点**：思路简洁，用 `map` 模拟，倒序处理避免复杂操作。
    - **核心代码**：
```cpp
const int N = 2e5 + 5;
map<string, bool> mp;
string s[N];

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = n; i >= 1; i--)
    {
        if (mp[s[i]]) continue;
        cout << s[i] << endl;
        mp[s[i]] = true;
    }
    return 0;
}
```
核心思想：倒序遍历存储的单词，用 `map` 判重，未出现过则输出并标记。

### 最优关键思路或技巧
反向思考，从后往前处理单词，利用 `map` 判重，避免正向操作时的复杂移动处理。

### 拓展
同类型题可拓展到处理其他元素的插入、移动和判重问题，如字符、数字等。类似算法套路可用于处理有顺序要求且需去重的场景，如处理事件序列、元素排列等。

### 洛谷相似题目推荐
- P1160 队列安排
- P1996 约瑟夫问题
- P2058 海港

### 个人心得
- UperFicial：表示这是个逗比题但自己 $WA$ 了一次，提醒做题时要细心，即使看似简单的题目也可能有坑。 

---
处理用时：25.49秒