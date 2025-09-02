# 题目信息

# Symmetric Encoding

## 题目描述

Polycarp has a string $ s $ , which consists of lowercase Latin letters. He encodes this string using the following algorithm:

- first, he constructs a new auxiliary string $ r $ , which consists of all distinct letters of the string $ s $ , written in alphabetical order;
- then the encoding happens as follows: each character in the string $ s $ is replaced by its symmetric character from the string $ r $ (the first character of the string $ r $ will be replaced by the last, the second by the second from the end, and so on).

For example, encoding the string $ s $ ="codeforces" happens as follows:

- the string $ r $ is obtained as "cdefors";
- the first character $ s_1 $ ='c' is replaced by 's';
- the second character $ s_2 $ ='o' is replaced by 'e';
- the third character $ s_3 $ ='d' is replaced by 'r';
- ...
- the last character $ s_{10} $ ='s' is replaced by 'c'.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974B/bdd77e5f1b5637622489d2d075a49b021a94a8b9.png) The string $ r $ and replacements for $ s $ ="codeforces".Thus, the result of encoding the string $ s $ ="codeforces" is the string "serofedsoc".

Write a program that performs decoding — that is, restores the original string $ s $ from the encoding result.

## 样例 #1

### 输入

```
5
10
serofedsoc
3
ttf
9
tlrhgmaoi
1
w
15
hnndledmnhlttin```

### 输出

```
codeforces
fft
algorithm
w
meetinthemiddle```

# AI分析结果

### 题目中文重写
# 对称编码

## 题目描述

波利卡普有一个字符串 $ s $，它由小写拉丁字母组成。他使用以下算法对这个字符串进行编码：
- 首先，他构造一个新的辅助字符串 $ r $，它由字符串 $ s $ 中所有不同的字母按字母表顺序排列组成；
- 然后进行编码：字符串 $ s $ 中的每个字符都被替换为字符串 $ r $ 中与其对称的字符（字符串 $ r $ 的第一个字符将被替换为最后一个，第二个被倒数第二个替换，依此类推）。

例如，对字符串 $ s $ ="codeforces" 进行编码的过程如下：
- 字符串 $ r $ 为 "cdefors"；
- 第一个字符 $ s_1 $ ='c' 被替换为 's'；
- 第二个字符 $ s_2 $ ='o' 被替换为 'e'；
- 第三个字符 $ s_3 $ ='d' 被替换为 'r'；
-...
- 最后一个字符 $ s_{10} $ ='s' 被替换为 'c'。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1974B/bdd77e5f1b5637622489d2d075a49b021a94a8b9.png) 字符串 $ r $ 以及 $ s $ ="codeforces" 的替换情况。因此，对字符串 $ s $ ="codeforces" 编码的结果是字符串 "serofedsoc"。

编写一个程序进行解码，即从编码结果中恢复原始字符串 $ s $。

## 样例 #1

### 输入
```
5
10
serofedsoc
3
ttf
9
tlrhgmaoi
1
w
15
hnndledmnhlttin
```

### 输出
```
codeforces
fft
algorithm
w
meetinthemiddle
```

### 综合分析与结论
- **思路对比**：所有题解核心思路一致，都是先对输入字符串排序去重得到辅助字符串 $r$，再建立字符映射关系，最后根据映射还原原始字符串。
- **算法要点**：排序去重是关键步骤，多数题解用 `sort` 函数排序，通过比较相邻元素或使用 `map` 去重。映射建立方式多样，有记录下标、用 `map` 存储对应关系等。
- **解决难点**：主要难点在于排序去重和映射建立。部分题解用 `map` 自动去重和排序，部分通过手动比较相邻元素去重。

### 评分较高的题解
- **作者：Dream_Mr_li（5星）**
    - **关键亮点**：思路清晰，代码注释详细，使用 `map` 去重和记录字符下标，方便后续对称输出。
    - **核心代码**：
```cpp
void solve(){
    cin>>n;
    int len_b=0;
    map<char,int>mp,bi;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mp[a[i]]++;
    }
    for(auto e:mp){
        b[++len_b]=e.first;
    }
    sort(b+1,b+len_b+1);
    for(int i=1;i<=len_b;i++){
        bi[b[i]]=i;
    }
    for(int i=1;i<=n;i++){
        cout<<b[len_b-bi[a[i]]+1];
    }
    cout<<endl;
}
```
核心思想：先统计字符出现次数去重，再将去重后的字符按字母表排序，记录每个字符下标，最后根据对称关系输出。
- **作者：cute_overmind（4星）**
    - **关键亮点**：代码结构清晰，使用 `vector` 和 `map` 实现排序去重和映射建立，逻辑简洁。
    - **核心代码**：
```cpp
void solve()
{
    int n;
    cin >> n;
    c.clear();
    mp.clear();
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 1;i <= n;i++) b[i] = a[i];
    sort(a + 1, a + n + 1);
    for(int i = 1;i <= n;i++)
        if(a[i]!= a[i - 1]) c.push_back(a[i]);
    for(int i = 0;i < c.size();i++) mp[c[i]] = c[c.size() - i - 1];
    for(int i = 1;i <= n;i++) cout << mp[b[i]];
    cout << '\n';
}
```
核心思想：先排序，再通过比较相邻元素去重，将去重后的字符存入 `vector`，建立映射关系，最后根据映射输出。
- **作者：_ayaka_（4星）**
    - **关键亮点**：思路简洁，使用 `map` 建立字符映射，代码可读性高。
    - **核心代码**：
```cpp
while (t--) {
    cin >> n >> s;
    string r = s;
    cnt = 1;
    sort(r.begin(), r.end());
    for (int i = 1; i < (int)r.length(); i++) {
        if (r[i]!= r[i - 1]) {
            r[cnt++] = r[i];
        }
    }
    for (int i = 0; i < cnt; i++) {
        q[r[i]] = r[cnt - i - 1];
    }
    for (int i = 0; i < (int)s.length(); i++) cout << q[s[i]];
    cout << "\n";
}
```
核心思想：对字符串排序去重，建立字符映射，根据映射还原原始字符串。

### 最优关键思路或技巧
- **数据结构**：使用 `map` 去重和建立字符映射，能简化代码逻辑，提高效率。
- **算法优化**：排序去重是核心步骤，合理利用 `sort` 函数和比较相邻元素可高效完成。

### 可拓展之处
同类型题可能会改变编码规则，如使用更复杂的映射关系或对字符串进行多次变换。类似算法套路是先分析编码规则，找到关键步骤，再模拟还原过程。

### 洛谷相似题目推荐
- P1055 [NOIP2008 普及组] ISBN 号码
- P1071 [NOIP2009 普及组] 潜伏者
- P1328 [NOIP2014 提高组] 生活大爆炸版石头剪刀布

### 个人心得摘录
题解中未包含个人心得内容。 

---
处理用时：38.39秒