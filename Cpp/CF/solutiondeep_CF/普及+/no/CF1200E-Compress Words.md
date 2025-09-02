# 题目信息

# Compress Words

## 题目描述

Amugae has a sentence consisting of $ n $ words. He want to compress this sentence into one word. Amugae doesn't like repetitions, so when he merges two words into one word, he removes the longest prefix of the second word that coincides with a suffix of the first word. For example, he merges "sample" and "please" into "samplease".

Amugae will merge his sentence left to right (i.e. first merge the first two words, then merge the result with the third word and so on). Write a program that prints the compressed word after the merging process ends.

## 样例 #1

### 输入

```
5
I want to order pizza
```

### 输出

```
Iwantorderpizza```

## 样例 #2

### 输入

```
5
sample please ease in out
```

### 输出

```
sampleaseinout```

# AI分析结果

### 题目内容（中文重写）
# 压缩单词

## 题目描述
Amugae 有一个由 $n$ 个单词组成的句子。他想把这个句子压缩成一个单词。Amugae 不喜欢重复，所以当他把两个单词合并成一个单词时，他会去掉第二个单词中与第一个单词的后缀重合的最长前缀。例如，他把 "sample" 和 "please" 合并成 "samplease"。

Amugae 会从左到右合并他的句子（即先合并前两个单词，然后将结果与第三个单词合并，依此类推）。编写一个程序，输出合并过程结束后的压缩单词。

## 样例 #1
### 输入
```
5
I want to order pizza
```
### 输出
```
Iwantorderpizza
```

## 样例 #2
### 输入
```
5
sample please ease in out
```
### 输出
```
sampleaseinout
```

### 算法分类
字符串

### 综合分析与结论
这些题解主要围绕如何合并多个字符串，去除相邻字符串的重复前后缀展开。核心思路是找出相邻字符串的最长公共前后缀，然后将非公共部分拼接起来。主要使用的算法有 KMP、哈希、Z 算法。

KMP 算法通过构造新字符串并计算其 next 数组来找到最长公共前后缀；哈希算法则是通过计算字符串的哈希值来判断前后缀是否相等；Z 算法通过计算 z 数组来找到可行的重合部分。

难点在于处理长字符串时的时间复杂度优化，以及避免前后缀跨界匹配的问题。许多题解通过截取字符串的部分内容、在字符串中间添加分隔符等方式来解决这些问题。

### 所选题解
- **yangrunze（4星）**
    - **关键亮点**：思路清晰，详细阐述了从最初的 KMP 实现到发现问题并逐步优化的过程，包括对拼接字符串长度的优化和防止跨界匹配的处理，代码注释丰富，可读性高。
    - **个人心得**：最初代码 TLE，经过分析发现拼接字符串过长导致 KMP 匹配时间过长，通过截取字符串长度优化；之后又出现 WA，通过在字符串中间添加分隔符解决跨界匹配问题。
- **Frozencode（4星）**
    - **关键亮点**：对题目要求的最大匹配长度解释清晰，结合样例进行说明，代码实现简洁明了，通过截取部分字符串和添加分隔符避免问题。
    - **个人心得**：无。
- **5k_sync_closer（4星）**
    - **关键亮点**：思路简洁，准确抓住 KMP 算法的核心，通过截取字符串后缀和添加特殊字符解决问题，代码简洁易懂。
    - **个人心得**：无。

### 重点代码
#### yangrunze 的 KMP 优化代码
```cpp
int nxt[1000005];//next数组（不要写next，在CF上是关键字，会CE）
void kmp(string s){
    int l=s.size();
    s=' '+s;//前面加个空格，让s下标从1开始
    nxt[0]=nxt[1]=0;//初始化next数组
    int j=0;//下标
    for(int i=2;i<=l;i++){
        while(j>0&&s[i]!=s[j+1])j=nxt[j];//如果不匹配，就借用已知信息跳到next
        if(s[i]==s[j+1])j++;//匹配成功！j++;
        nxt[i]=j;//更新next数组的信息
    } 
}
int main(){
    ios::sync_with_stdio(false);//让cin变得快一点
    int n;
    cin>>n;
    string s,ans;
    cin>>ans;//先拿第一个字符串当成答案，后面逐步合并
    for(int i=2;i<=n;i++){
        cin>>s;//输入
        int l=min(s.size(),ans.size());//真正需要KMP的长度        
        string ss=s+"#*@$woxiangqiediaoYnoi,yingyingying~~~"+ans.substr(ans.size()-l,l);//利用string里的substr函数，截取从下标ans.size()-l，长度为l的子串，也就是后l个字符
        kmp(ss);//进行kmp
        for(int j=nxt[ss.size()];j<s.size();j++)//更新不是公共部分（也就是下标>=next[ss.size()]的部分）到ans里
            ans+=s[j];
    }
    cout<<ans;//输出
} 
```
**核心实现思想**：先输入第一个字符串作为初始答案，然后依次输入后续字符串。对于每个新输入的字符串，截取答案字符串的后 `min(s.size(), ans.size())` 个字符，与新字符串拼接成新的字符串，并在中间添加分隔符。对新字符串进行 KMP 计算，得到最长公共前后缀的长度，将新字符串中非公共部分添加到答案字符串中。

#### Frozencode 的 KMP 实现代码
```cpp
int n,len,anslen,top,minn,kmp[maxn];
char c[maxn],ans[maxn];
int main()
{ 
    cin>>n;
    for(int i = 1;i <= n;i++){
        scanf("%s",c + 1);
        len = strlen(c + 1);
        minn = min(anslen,len);//截取长度。
        top = len;
        c[++top] = '#';//加个奇怪字符防止最大匹配长度超过待拼接串的长度。
        for(int j = 1;j <= minn;j++)c[++top] = ans[anslen - (minn - j)];//拼接。
        for(int j = 1;j < top;j++){
            ll k = kmp[j];
            while(k && c[k + 1] != c[j + 1])k = kmp[k];
            if(c[k + 1] == c[j + 1])k++;
            kmp[j + 1] = k;
        }//求kmp数组的值
        for(int j = kmp[top] + 1;j <= len;j++)ans[++anslen] = c[j];//更新当前拼接好的串。
    }
    for(int i = 1;i <= anslen;i++)cout<<ans[i];
    return 0;
}
```
**核心实现思想**：依次输入每个字符串，截取答案字符串的后 `min(anslen, len)` 个字符与当前字符串拼接，在中间添加分隔符。计算拼接后字符串的 KMP 数组，根据 KMP 数组的结果将当前字符串中非公共部分添加到答案字符串中。

#### 5k_sync_closer 的 KMP 代码
```cpp
int n, K[1000050];
string s, q, a;
int main()
{
    cin >> n;
    for (int i = 1, l, m; i <= n; ++i)
    {
        cin >> s;
        l = min(s.length(), q.length());
        a = s + '\0' + q.substr(q.length() - l); //截取 q 的后缀，加入特殊字符
        m = a.length();
        a = '\0' + a;
        for (int i = 2, j = 0;i <= m;++i) //KMP
        {
            while(j && a[i] != a[j + 1]) j = K[j];
            K[i] = j += a[i] == a[j + 1];
        }
        q += s.substr(K[m]);
    }
    cout << q;
    return 0;
}
```
**核心实现思想**：依次输入每个字符串，截取答案字符串的后 `min(s.length(), q.length())` 个字符与当前字符串拼接，在中间添加特殊字符 `\0`。对拼接后的字符串进行 KMP 计算，根据 KMP 数组的结果将当前字符串中非公共部分添加到答案字符串中。

### 可拓展之处
同类型题目可能会有不同的字符串合并规则，或者对时间复杂度和空间复杂度有更高的要求。类似算法套路包括使用更复杂的字符串匹配算法（如 AC 自动机），或者结合其他数据结构（如字典树）来解决问题。

### 推荐题目
- [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
- [P5410 【模板】扩展 KMP（Z 函数）](https://www.luogu.com.cn/problem/P5410)
- [P3193 [HNOI2008]GT考试](https://www.luogu.com.cn/problem/P3193)

### 个人心得总结
- 许多题解作者在实现过程中都遇到了 TLE 问题，原因是拼接的字符串过长导致匹配时间过长。通过截取字符串的部分内容可以有效优化时间复杂度。
- 部分作者遇到 WA 问题，是因为前后缀跨界匹配，在字符串中间添加分隔符可以解决这个问题。
- 还有作者在使用哈希算法时被 Hack，需要采用随机多 base 多模数等方法来提高哈希的安全性。

---
处理用时：73.60秒