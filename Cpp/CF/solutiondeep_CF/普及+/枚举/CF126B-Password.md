# 题目信息

# Password

## 题目描述

Asterix，Obelix 和他们的临时伙伴 Suffix、Prefix 已经最终找到了和谐寺。然而和谐寺大门紧闭，就连 Obelix 的运气也没好到能打开它。

不久他们发现了一个字符串 $S\ (1\leqslant\vert S\vert\leqslant1000000)$，刻在和谐寺大门下面的岩石上。Asterix 猜想那一定是打开寺庙大门的密码，于是就大声将字符串朗读了出来，然而并没有什么事发生。于是 Asterix 又猜想密码一定是字符串 $S$ 的子串 $T$。

Prefix 认为 $T$ 是 $S$ 的前缀，Suffix 认为 $T$ 是 $S$ 的后缀，Obelix 却认为 $T$ 应该是 $S$ 中的某一部分，也就是说，$T$ 既不是 $S$ 的前缀，也不是 $S$ 的后缀。

Asterix 选择子串 $T$ 来满足所有伙伴们的想法。同时，在所有可以被接受的子串变形中，Asterix 选择了最长的一个。当 Asterix 大声读出子串 $T$ 时，寺庙的大门开了。（也就是说，你需要找到既是 $S$ 的前缀又是 $S$ 的后缀同时又在 $S$ 中间出现过的最长子串）

现在给你字符串 $S$，你需要找到满足上述要求的子串 $T$。

## 样例 #1

### 输入

```
fixprefixsuffix
```

### 输出

```
fix```

## 样例 #2

### 输入

```
abcdabc
```

### 输出

```
Just a legend```

# AI分析结果

### 题目内容
# Password
## 题目描述
Asterix、Obelix和他们的临时伙伴Suffix、Prefix最终找到了和谐寺。然而，和谐寺大门紧闭，就连Obelix的运气也没能好到打开它。
不久后，他们发现了一个字符串 $S\ (1\leqslant\vert S\vert\leqslant1000000)$，刻在和谐寺大门下方的岩石上。Asterix猜想那一定是打开寺庙大门的密码，于是大声将字符串朗读了出来，然而并没有什么事发生。于是Asterix又猜想密码一定是字符串 $S$ 的子串 $T$。
Prefix认为 $T$ 是 $S$ 的前缀，Suffix认为 $T$ 是 $S$ 的后缀，Obelix却认为 $T$ 应该是 $S$ 中的某一部分，也就是说，$T$ 既不是 $S$ 的前缀，也不是 $S$ 的后缀。
Asterix选择子串 $T$ 来满足所有伙伴们的想法。同时，在所有可以被接受的子串变形中，Asterix选择了最长的一个。当Asterix大声读出子串 $T$ 时，寺庙的大门开了。（也就是说，你需要找到既是 $S$ 的前缀又是 $S$ 的后缀同时又在 $S$ 中间出现过的最长子串）
现在给你字符串 $S$，你需要找到满足上述要求的子串 $T$。
## 样例 #1
### 输入
```
fixprefixsuffix
```
### 输出
```
fix
```
## 样例 #2
### 输入
```
abcdabc
```
### 输出
```
Just a legend
```

### 综合分析与结论
这些题解主要围绕如何找到字符串 $S$ 中既是前缀又是后缀且在中间出现过的最长子串展开，大部分题解使用了KMP算法，部分使用字符串哈希、Z算法、后缀自动机（SAM）等方法。
1. **KMP算法思路**：利用KMP的next数组求出既是前缀又是后缀的子串长度。由于要满足在中间出现，需对next数组进一步处理。如找出next[1~n - 1]中的最大值maxn，若next[n]大于maxn，则不断跳转next[n]直到其小于等于maxn，若最终为0则无解，否则找到符合条件的子串。
2. **字符串哈希思路**：先通过哈希预处理求出所有合法前缀，再二分查找判断是否存在对应的中间子串。
3. **Z算法思路**：通过Z数组求出每个位置开始的最长与前缀相同子串长度，利用vis数组标记已出现的长度，判断是否存在符合条件子串。
4. **SAM思路**：通过后缀自动机和线段树合并判断子串是否在指定区间出现，从而找到符合条件子串。

### 所选的题解
- **作者：MyukiyoMekya (赞：35)  星级：4星**
    - **关键亮点**：采用字符串哈希算法，先 $O(n)$ 找出所有合法前缀，再二分查找判断是否存在对应的中间子串，整体思路清晰，复杂度为 $\mathcal O(n\log n)$。
    - **重点代码**：
```cpp
// 计算哈希值
inline int calc(int l,int r)
{
    return (f[r]-f[l-1]*g[r-l+1]%p+p)%p;
}
// 检查是否存在符合条件子串
inline bool check(int len,int val)
{
    for(int i=2;i+len-1<n;++i)
        if(val==calc(i,i+len-1))
            return true;
    return false;
}
signed main(void)
{
    std::scanf("%s",s+1),n=std::strlen(s+1);
    g[0]=1;
    for(int i=1;i<=n;++i)
        g[i]=g[i-1]*base%p;
    for(int i=1;i<=n;++i)
        f[i]=(f[i-1]*base%p+s[i])%p;
    std::vector<int> dr;
    for(int i=1;i<=n-2;++i)
        if(calc(1,i)==calc(n-i+1,n))
            dr.pb(i);
    reg int l=0,r=(int)dr.size()-1,ans=0,mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(check(dr[mid],calc(1,dr[mid])))
            ans=dr[mid],l=mid+1;
        else
            r=mid-1;
    }
    if(!ans)
        return std::puts("Just a legend"),0;
    for(int i=1;i<=ans;++i)
        std::putchar(s[i]);ln;
    return 0;
}
```
核心实现思想：先预处理出字符串的哈希值，然后找出所有既是前缀又是后缀的子串长度存于dr数组，通过二分查找在dr数组中找到最长且在中间出现过的子串。
- **作者：Chemist (赞：26)  星级：4星**
    - **关键亮点**：利用KMP算法求next数组，通过预处理next数组中的最大值max{next[1~n - 1]}，对next[n]进行调整，找到符合条件的最长子串，思路清晰，代码简洁。
    - **重点代码**：
```cpp
void cal()//求出next数组
{
    next[1]=0;
    for(int i=2,j=0;i<=n;i++){
        while(j&&a[i]!=a[j+1])j=next[j];
        if(a[i]==a[j+1])j++;
        next[i]=j;
        if(i!=n)maxx=max(next[i],maxx);
        //找到next数组的最大值
    }
}
int main()
{
    cin>>a+1;
    n=strlen(a+1);
    cal();
    int x=next[n];
    if(x==0)printf("Just a legend\n");
    else{
        while(x>maxx)x=next[x];
        //找到小于max{next[1~n-1]}的最大匹配长度
        if(x==0){
            printf("Just a legend\n");
            return 0;
        }
        for(int i=2;i<n;i++)
            if(x==next[i]){
                for(int j=i-next[i]+1;j<=i;j++)
                    //i-next[i]+1为答案子串的左端点
                    printf("%c",a[j]);
                printf("\n");
                return 0;
            }
    }
    return 0;
} 
```
核心实现思想：通过cal函数求出next数组并记录maxx，然后对next[n]进行调整，最后遍历next数组找到符合条件的子串。
- **作者：Cry_For_theMoon (赞：5)  星级：4星**
    - **关键亮点**：对KMP算法理解深刻，利用KMP求next数组找到既是前缀又是后缀的子串，证明了1~maxn这些值都存在于next[2~n - 1]中，简化了判断中间子串是否存在的过程。
    - **重点代码**：
```cpp
int main(){
    cin>>(str+1);
    n=strlen(str+1);
    fail[1]=0;
    int j=0;
    for(int i=2;i<=n;i++){
        while(j&&str[j+1]!=str[i]){
            j=fail[j];
        }
        if(str[j+1]==str[i])j++;
        fail[i]=j;
        if(i!=n){
            maxn=max(maxn,j);
        } 
    }
    j=fail[n];
    if(maxn==0 || j==0){
        printf("Just a legend");
        return 0;
    }
    while(j>maxn){
        j=fail[j];
    }
    if(j==0){
        printf("Just a legend");
        return 0; 
    }
    for(int k=1;k<=j;k++){
        printf("%c",str[k]);
    }
    printf("\n");
    return 0;
}
```
核心实现思想：先求出next数组并记录maxn，对next[n]进行调整，由于证明了1~maxn存在于next[2~n - 1]中，所以直接输出长度为j的子串。

### 最优关键思路或技巧
1. **KMP算法巧用**：通过KMP算法的next数组快速找到既是前缀又是后缀的子串，再结合对中间子串存在性的判断，优化了查找符合条件最长子串的过程。如通过记录next[1~n - 1]的最大值来调整next[n]，避免了不必要的遍历。
2. **性质证明简化判断**：如证明1~maxn这些值都存在于next[2~n - 1]中，简化了判断中间子串是否存在的过程，减少代码复杂度。

### 可拓展之处
同类型题可考察字符串匹配、子串查找等相关问题，类似算法套路如利用KMP、Z算法、字符串哈希、后缀自动机等解决字符串相关问题。例如，在判断子串是否在字符串中多次出现且满足特定位置关系时，可使用类似思路。

### 推荐洛谷题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)：基础的KMP算法模板题，用于巩固KMP算法的理解和实现。
2. [P5410 【模板】扩展KMP（Z函数）](https://www.luogu.com.cn/problem/P5410)：考察Z函数的应用，与本题部分解法相关，可加深对字符串匹配算法的理解。
3. [P4051 [JSOI2007]字符加密](https://www.luogu.com.cn/problem/P4051)：涉及后缀数组和字符串循环同构问题，可拓展对字符串算法的应用能力。

### 个人心得摘录与总结
暂无个人心得相关内容。 

---
处理用时：43.52秒