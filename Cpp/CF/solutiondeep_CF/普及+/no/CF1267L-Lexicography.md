# 题目信息

# Lexicography

## 题目描述

Lucy likes letters. She studied the definition of the lexicographical order at school and plays with it.

At first, she tried to construct the lexicographically smallest word out of given letters. It was so easy! Then she tried to build multiple words and minimize one of them. This was much harder!

Formally, Lucy wants to make $ n $ words of length $ l $ each out of the given $ n \cdot l $ letters, so that the $ k $ -th of them in the lexicographic order is lexicographically as small as possible.

## 样例 #1

### 输入

```
3 2 2
abcdef
```

### 输出

```
af
bc
ed```

## 样例 #2

### 输入

```
2 3 1
abcabc
```

### 输出

```
aab
bcc
```

# AI分析结果

### 题目内容中文重写
# 字典序问题

## 题目描述
露西喜欢字母。她在学校学习了字典序的定义，并开始玩相关的游戏。

起初，她尝试用给定的字母构造出字典序最小的单词。这太简单了！接着，她尝试构造多个单词，并让其中一个单词的字典序尽可能小。这就难多了！

形式上，露西想从给定的 $n \cdot l$ 个字母中构造出 $n$ 个长度为 $l$ 的单词，使得按字典序排列后的第 $k$ 个单词的字典序尽可能小。

## 样例 #1

### 输入
```
3 2 2
abcdef
```

### 输出
```
af
bc
ed
```

## 样例 #2

### 输入
```
2 3 1
abcabc
```

### 输出
```
aab
bcc
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心目标都是构造出 $n$ 个长度为 $l$ 的单词，使第 $k$ 个单词的字典序最小。各题解思路大多基于贪心策略，先对字母排序，再合理分配字母到各个单词中。

不同题解的差异在于具体的分配方式：
- 灵茶山艾府的题解采用竖着填字母的方式，尽量均匀分配，并维护从哪一行开始填。
- yuzhechuan 的题解通过倒着扫描确定哪些串“有可能”大于等于第 $k$ 个串，刻意插小字符。
- gyh20 的题解将字符从小到大排列，在前 $i - 1$ 个都与第 $k$ 个相同且位置小于 $k$ 时进行分配。
- Cry_For_theMoon 的题解用桶维护可用字符数量，根据不同情况分配字符。

### 所选题解
- 灵茶山艾府的题解（4星）：关键亮点在于通过竖着填字母的方式，均匀分配字母，使第 $k$ 个字符串的字典序尽量小。同时，维护每列从哪个字符串开始填，优化了分配过程。
- yuzhechuan 的题解（4星）：思路清晰，通过确定“有可能”大于等于第 $k$ 个串的区间，刻意插小字符，有效降低第 $k$ 个串的字典序。

### 重点代码
#### 灵茶山艾府的题解
```go
func main() {
    in := bufio.NewReader(os.Stdin)
    var n, m, k, p, i0 int
    var s []byte
    Fscan(in, &n, &m, &k, &s)
    sort.Slice(s, func(i, j int) bool { return s[i] < s[j] })

    ans := make([][]byte, n)
    for i := range ans {
        ans[i] = make([]byte, m)
    }
    for j := 0; j < m; j++ {
        for i := i0; i < k; i++ { // 第 j 列从第 i0 行开始填
            ans[i][j] = s[p]
            if i > i0 && s[p] != s[p-1] {
                i0 = i
            }
            p++
        }
    }

    for _, t := range ans {
        for j, b := range t {
            if b == 0 { // 剩余没填的字母
                t[j] = s[p]
                p++
            }
        }
        Printf("%s\n", t)
    }
}
```
核心实现思想：先对字母排序，然后竖着填字母，尽量均匀分配。当某一列填的字母不一样时，更新下一列开始填的行号。最后将剩余未填的字母依次填入。

#### yuzhechuan 的题解
```cpp
signed main(){
    read(n);read(l);read(k);;
    scanf("%s",s+1);
    sort(s+1,s+1+n*l); //贪心的排个序
    for(int i=1;i<=l;i++){
        int pos=k; //区间[pos,k-1]都是有可能大于等于k的串，因此要特意插小字符把他们扼杀掉
        while(pos>=2&&ans[pos-1][i-1]==ans[k][i-1]) pos--;
        for(int j=pos;j<=k;j++) ans[j][i]=s[++use]; //按顺序插小字符
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=l;j++) if(ans[i][j]=='\0') //这个位置上没有字符
            ans[i][j]=s[++use];
    for(int i=1;i<=n;i++) printf("%s\n",ans[i]+1);
}
```
核心实现思想：先对字母排序，然后逐位确定单词。对于每一位，倒着扫描确定“有可能”大于等于第 $k$ 个串的区间，在该区间内按顺序插小字符。最后将剩余未填的字母依次填入。

### 最优关键思路或技巧
- 贪心策略：先对字母进行排序，保证从最小的字母开始分配。
- 竖着填字母：尽量均匀地分配字母，使第 $k$ 个字符串的字典序尽量小。
- 确定关键区间：通过倒着扫描等方式确定哪些串“有可能”大于等于第 $k$ 个串，刻意插小字符降低第 $k$ 个串的字典序。

### 可拓展之处
同类型题或类似算法套路：
- 构造满足特定条件的字符串或序列，如构造字典序最大或最小的排列。
- 基于贪心策略的分配问题，如资源分配、任务调度等。

### 推荐洛谷题目
1. P1094 [NOIP2007 普及组] 纪念品分组：https://www.luogu.com.cn/problem/P1094
2. P1223 排队接水：https://www.luogu.com.cn/problem/P1223
3. P2240 【深基12.例1】部分背包问题：https://www.luogu.com.cn/problem/P2240

### 个人心得
Cry_For_theMoon 的题解提到“这里有个把 bucket 用 char 存的爆零人”，总结为在处理字符数量统计时，要注意数据类型的选择，避免因数据类型范围不足导致错误。 

---
处理用时：51.29秒