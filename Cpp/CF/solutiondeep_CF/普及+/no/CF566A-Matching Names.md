# 题目信息

# Matching Names

## 题目描述

Teachers of one programming summer school decided to make a surprise for the students by giving them names in the style of the "Hobbit" movie. Each student must get a pseudonym maximally similar to his own name. The pseudonym must be a name of some character of the popular saga and now the teachers are busy matching pseudonyms to student names.

There are $ n $ students in a summer school. Teachers chose exactly $ n $ pseudonyms for them. Each student must get exactly one pseudonym corresponding to him. Let us determine the relevance of a pseudonym $ b $ to a student with name $ a $ as the length of the largest common prefix $ a $ and $ b $ . We will represent such value as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF566A/49184e0d721201acb7ec1d32721635b1fa5d0628.png). Then we can determine the quality of matching of the pseudonyms to students as a sum of relevances of all pseudonyms to the corresponding students.

Find the matching between students and pseudonyms with the maximum quality.

## 说明/提示

The first test from the statement the match looks as follows:

- bill $ → $ bilbo (lcp = 3)
- galya $ → $ galadriel (lcp = 3)
- gennady $ → $ gendalf (lcp = 3)
- toshik $ → $ torin (lcp = 2)
- boris $ → $ smaug (lcp = 0)

## 样例 #1

### 输入

```
5
gennady
galya
boris
bill
toshik
bilbo
torin
gendalf
smaug
galadriel
```

### 输出

```
11
4 1
2 5
1 3
5 2
3 4
```

# AI分析结果

### 题目内容
# 匹配名字

## 题目描述
某编程暑期学校的老师们决定给学生们一个惊喜，用《霍比特人》电影风格给他们取名字。每个学生必须得到一个与自己名字尽可能相似的化名。这个化名必须是这部热门系列电影中某个角色的名字，现在老师们正忙着将化名与学生名字进行匹配。

暑期学校有 $n$ 个学生。老师们为他们选了恰好 $n$ 个化名。每个学生必须恰好得到一个与他对应的化名。我们将化名 $b$ 与名字为 $a$ 的学生的相关性定义为 $a$ 和 $b$ 的最长公共前缀的长度。我们将这个值表示为 $lcp(a, b)$。那么我们可以将化名与学生的匹配质量定义为所有化名与相应学生的相关性之和。

找出匹配质量最高的学生与化名之间的匹配方式。

## 说明/提示
题目中的第一个测试用例的匹配情况如下：
- bill $→$ bilbo（最长公共前缀长度 = 3）
- galya $→$ galadriel（最长公共前缀长度 = 3）
- gennady $→$ gendalf（最长公共前缀长度 = 3）
- toshik $→$ torin（最长公共前缀长度 = 2）
- boris $→$ smaug（最长公共前缀长度 = 0）

## 样例 #1
### 输入
```
5
gennady
galya
boris
bill
toshik
bilbo
torin
gendalf
smaug
galadriel
```
### 输出
```
11
4 1
2 5
1 3
5 2
3 4
```
### 算法分类
贪心

### 题解综合分析与结论
这两道题解思路基本一致，均是利用Trie树结合贪心策略解题。思路要点在于将学生名字和化名存入同一颗Trie树，通过 $0$ 和 $1$ 区分，在Trie树的深结点处，能匹配则匹配，每次选取公共前缀最长的学生和化名进行匹配，因为当前最大的公共前缀对于整体和最大的目标是最优的，若当前不选，之后无法找到更优匹配。

### 所选的题解
- **作者：skylee (2赞) - 4星**
    - **关键亮点**：代码实现完整，详细展示了Trie树的插入、删除及匹配求解过程。通过Trie树节点上维护两个集合，分别存储学生名字和化名的编号，在遍历Trie树时，从深的节点开始匹配，找到匹配对后从集合中删除对应编号，同时累加匹配深度到答案。
    - **重点代码 - Trie树类**：
```cpp
class Trie {
    private:
        std::set<int> set[L][2];
        int ch[L][26],par[L],sz;
        int idx(const char &c) const {
            return c-'a';
        }
        void erase(int p,const int &x,const bool &t) {
            while(p) {
                set[p][t].erase(x);
                p=par[p];
            }
            set[0][t].erase(x);
        }
    public:
        void insert(char s[],const int &id,const bool &t) {
            set[0][t].insert(id);
            for(register int i=0,p=0;s[i];i++) {
                const int c=idx(s[i]);
                if(!ch[p][c]) {
                    ch[p][c]=++sz;
                    par[ch[p][c]]=p;
                }
                p=ch[p][c];
                set[p][t].insert(id);
            }
        }
        void solve(const int &p,const int &dep) {
            for(register int i=0;i<26;i++) {
                if(ch[p][i]) {
                    solve(ch[p][i],dep+1);
                }
            }
            while(!set[p][0].empty()&&!set[p][1].empty()) {
                ans+=dep;
                const int x=*set[p][0].begin();
                const int y=*set[p][1].begin();
                v.push_back(std::make_pair(x,y));
                erase(p,x,0);
                erase(p,y,1);
            }
        }
};
```
    - **核心实现思想**：`insert` 函数用于将字符串插入Trie树，并在对应节点的集合中记录编号；`erase` 函数用于从Trie树节点集合中删除编号；`solve` 函数通过递归遍历Trie树，在每个节点处找到匹配对并更新答案和记录匹配方案。
- **作者：qfpjm (0赞) - 3星**
    - **关键亮点**：思路阐述清晰，简洁说明了利用Trie树贪心的思路，即顺着前缀在Trie树上尽可能深地匹配，每次选择公共前缀最长的学生和笔名匹配。但未给出代码实现。

### 最优关键思路或技巧
利用Trie树存储字符串，能高效地找到公共前缀。结合贪心策略，在Trie树的每个节点处优先选择最长公共前缀的匹配对，保证整体匹配质量最优。

### 同类型题或类似算法套路拓展
此类题目通常围绕字符串匹配及优化匹配指标展开，常见套路是利用Trie树优化字符串前缀查找，结合贪心策略解决匹配问题。

### 洛谷相似题目推荐
- [P2580 [ZJOI2006] 书架](https://www.luogu.com.cn/problem/P2580)
- [P3804 【模板】后缀自动机](https://www.luogu.com.cn/problem/P3804)
- [P4555 [国家集训队]最长双回文串](https://www.luogu.com.cn/problem/P4555)

---
处理用时：47.72秒