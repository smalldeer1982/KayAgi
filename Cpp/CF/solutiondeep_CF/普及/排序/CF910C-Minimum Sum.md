# 题目信息

# Minimum Sum

## 题目描述

Petya 有一个长度为n的正整数序列 $a_{1},a_{2},...,a_{n}$。他的朋友Vasya 想要捉弄他，Vasya用一个字母替换了Petya 的号码中的所有数字。

他用小写字母‘a’到‘j’中的一个字母替换了所有数字 0，用另一个字母替换了所有 1，依次类推。对于不同的两个数字，Vasya 用‘a’到‘j’中不同的字母。

你的任务是还原 Petya 的序列。还原得到的数字应是没有前导零（数字开头没有零）的正整数。由于可能有多种方式实现，所以要求恢复后的序列总和最小。保证初始时序列中数字没有前导零。

## 样例 #1

### 输入

```
3
ab
de
aj
```

### 输出

```
47
```

## 样例 #2

### 输入

```
5
abcdef
ghij
bdef
accbd
g
```

### 输出

```
136542
```

## 样例 #3

### 输入

```
3
aa
jj
aa
```

### 输出

```
44
```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是贪心算法。要点在于计算每个字母对总和的贡献（即权重），按权重排序，同时注意前导零的限制，让权重高的字母对应小的数字以达到总和最小。

- **思路对比**：多数题解先计算字母权重，再排序，最后分配数字计算总和；部分题解使用结构体存储字母信息，部分用 `pair` 或 `unordered_map`。
- **算法要点**：计算权重时，根据字母在字符串中的位置确定其权重，如在个位权重为 1，十位为 10 等；排序后，找到可赋为 0 的权重最大的字母，其余字母按权重依次分配 1 - 9。
- **难点解决**：前导零是关键难点，各题解通过标记字符串首字母来处理，确保其不被赋为 0。

### 所选题解
- **作者：chengni (赞：3)  4星**
    - **关键亮点**：思路清晰，代码简洁，通过自定义结构体存储字母信息，利用排序和简单的循环实现贪心算法。
    - **个人心得**：无
- **作者：codeLJH114514 (赞：2)  4星**
    - **关键亮点**：详细阐述解题思路，代码结构清晰，使用自定义结构体和重载小于号进行排序，易于理解。
    - **个人心得**：无
- **作者：_frog (赞：0)  4星**
    - **关键亮点**：对题目进行详细分析，给出时间复杂度，代码规范，使用结构体排序实现贪心算法。
    - **个人心得**：无

### 重点代码
#### 作者：chengni
```cpp
struct node {
    int a,b;
}t[100000];

bool cmp(node x,node y){
    return x.a>y.a;
}

int main(){
    int n=read();
    for(int i=1;i<=n;i++){
        cin>>c;
        int l=strlen(c);
        for(int j=0;j<l;j++){
            t[c[j]-'a'+1].a+=pos(l-j-1);
            if(j==0) t[c[j]-'a'+1].b=1;
        }
    }
    sort(t+1,t+11,cmp);
    for(int i=1;i<=10;i++){
        if(t[i].b==0 && t[i].a!=0){
            t[i].a=0;
            break;
        }
    }
    int ans=0,sum=1;
    for(int i=1;i<=10;i++){
        if(t[i].a!=0){
            ans+=t[i].a*sum;
            sum++;
        }
    }
    cout<<ans<<endl;
} 
```
**核心思想**：用结构体 `node` 存储字母的权重和是否为首字母信息，计算权重后排序，找到可赋 0 的字母，最后计算总和。

#### 作者：codeLJH114514
```cpp
class Node{
    public:
        int v, k; 
        bool t; 
        char ch; 
        bool operator<(const Node& n) const& {
            return k > n.k;
        } 
} d[12]; 

int main() {
    cin >> n;
    for (int i = 1; i <= 10; i++) d[i].ch = i + 'a' - 1;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        d[s[0] - 'a' + 1].t = true;
        for (int j = 0; j < s.size(); j++)
            d[s[j] - 'a' + 1].k += pow(10, s.size() - j - 1);
    }
    sort(d + 1, d + 10 + 1);
    int zero = 0;
    for (int i = 1; i <= 10; i++) {
        if (not d[i].t) {
            zero = i;
            break;
        }
    }
    for (int i = 1; i <= 10; i++) d[i].v = -1;
    d[zero].v = 0;
    int cnt = 1;
    for (int i = 1; i <= 10; i++)
        if (d[i].v == -1)
            d[i].v = cnt++;
    int ans = 0;
    for (int i = 1; i <= 10; i++)
        ans += d[i].v * d[i].k;
    cout << ans;
    return 0;
}
```
**核心思想**：使用自定义类 `Node` 存储字母信息，计算权重后排序，找到可赋 0 的字母，依次分配数字，最后计算总和。

#### 作者：_frog
```cpp
struct Node {
    bool can_be_0;
    ll val;
    char name;
} a[11];

bool cmp(Node x, Node y) {
    if (x.val != y.val) return x.val < y.val; 
    return x.name < y.name;
}

int main() {
    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> str[i];
        flg[str[i][0] - 'a'] = 1;
        ll s = 1;
        for (ll j = str[i].length() - 1; j >= 0; j--) {
            t[str[i][j] - 'a'] += s;
            s *= 10;
        }
    }
    for (ll i = 0; i < 10; i++) {
        a[i].can_be_0 = !flg[i];
        a[i].name = i + 'a';
        a[i].val = t[i];
    }
    sort(a, a + 10, cmp);
    for (ll i = 9; i >= 0; i--) {
        if (a[i].can_be_0) {
            zero_ind = i;
            break;
        }
    }
    ll w = 9;
    for (ll i = 0; i < 10; i++) {
        if (i == zero_ind) {
            continue;
        }
        ans += a[i].val * w;
        w--;
    }
    cout << ans;
    return 0;
}
```
**核心思想**：用结构体 `Node` 存储字母信息，计算权重后排序，找到可赋 0 的字母，从大到小分配数字，最后计算总和。

### 最优关键思路或技巧
- **贪心策略**：让权重高的字母对应小的数字，以达到总和最小。
- **标记前导零**：通过标记字符串首字母，确保其不被赋为 0。
- **结构体存储信息**：使用结构体或类存储字母的权重、是否为首字母等信息，方便排序和处理。

### 可拓展之处
同类型题如数字替换使表达式值最小、字符映射使字符串总价值最小等。类似算法套路为贪心算法，先分析每个元素的贡献，再根据贡献大小分配资源，同时注意特殊限制条件。

### 推荐题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)

### 个人心得摘录与总结
- **作者：1qaz234567pzy**：提到交了三遍才过，说明实现过程中可能遇到一些细节问题，如前导零的处理等，提醒我们在做题时要注意边界条件和特殊情况。

---
处理用时：52.33秒