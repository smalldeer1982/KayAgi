# [BalticOI 2005] Ancient Manuscript

## 题目描述

给定 Baltic 字符串的定义为：

- 全部为小写字母
- 最多只能有 $V_C$ 个连续的元音
- 最多只能有 $C_C$ 个连续的辅音
- 最多只能有 $V_E$ 个连续的元音相等
- 最多只能有 $C_E$ 个连续的辅音相等

`aeiou` 为元音，除了这五个字母之外的 21 个字母为辅音。

现在给定一个字符串，一些字符为小写字母一些字符为 `*`，您可以把 `*` 替换成任意一个小写字母。

求通过替换能使得这个字符串得到的不同的 Baltic 字符串的种类数。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，$1 \le V_E \le V_C \le 4$，$1 \le C_E \le C_C \le 4$，$1 \le\ $字符串的长度$\ \le 15$。

#### 说明

翻译自 [BalticOI 2005 Day2 A Ancient Manuscript](https://boi.cses.fi/files/boi2005_day2.pdf)。

## 样例 #1

### 输入

```
1 1 1 1
a** ```

### 输出

```
105```

## 样例 #2

### 输入

```
1 1 1 1
b*i ```

### 输出

```
0```

## 样例 #3

### 输入

```
1 2 1 2
ancient ```

### 输出

```
1```

## 样例 #4

### 输入

```
4 4 4 4
man****ipt ```

### 输出

```
261870```

## 样例 #5

### 输入

```
2 2 2 2
*boi* ```

### 输出

```
546```

# 题解

## 作者：Echoternity (赞：3)

暴力不行，考虑 dp。

首先，我们应该清楚的是，对于一个字符串，能够影响答案的只有其中的 `*` 了。如果该字符串没有`*` 的话，那它的答案就是 $1$ 了。（样例3）

### 考虑状态

第一维肯定是当前到了第 $i$ 个位置了。而后呢，首先可以考虑再开四维分别指代题目中的四个限制。但这样似乎有点浪费空间，而且转移时也不太好转移。所以再压缩空间，用 $dp[i][j][k][l]$ 来表示当前第 $i$ 个位置，连续相同的字符 $j$ 个，相同种类的字符 $k$ 个，当前位置为 $l$ 的状态。可以省掉一维。

~~这样看来似乎有点像数位 dp 了呢~~

### 考虑转移

首先，我们只需要在当前位置为 `*` 时，或者枚举字符刚好是该位字符时，才会进行转移。

如果该位字符已经固定，则直接转移即可。

如果两个字符相同，则有

$dp_{i,j,k,s}=dp_{i,j,k,s}+dp_{i-1,j-1,k-1,s}$

而如果不一样，但是同种类，则有

$dp_{i,j,1,s}=dp_{i,j,1,s}+dp_{i-1,j-1,l-1,s_0}$

如果完全不一样，且种类也不一样，则有

$dp_{i,1,1,s}=dp_{i,1,1,s}+dp_{i-1,j,k,l}$

这就是三种情况。

### 答案的统计

$res=\sum\limits_{j=1,k=1}^{j=C_{type},k=E_{type}}dp_{n,j,k,s_n}$

就好了。

这种 dp，如果能想到的话，其实还是蛮简单的。

AC Code:
``` cpp

省略了冗长的预处理
int E[3],C[3],val[30];
ll dp[30][30][30][30];
char str[30];
inline bool expr(int b)
{
    if(b==0||b==4||b==8||b==14||b==20) return 1;
    return 0;
}
int main()
{
    // freopen("dp.in","r",stdin);
    // freopen("dp.out","w",stdout);
    read(E[1],C[1],E[0],C[0]);
    scanf("%s",str+1);
    int len=strlen(str+1);
    for(int i=1;i<=len;++i)
        if(str[i]=='*') val[i]=26;
        else val[i]=str[i]-'a';
    for(int i=0;i<=25;++i)
        if(val[1]==26||val[1]==i)
            dp[1][1][1][i]=1;
    for(int i=2;i<=len;++i)
        for(int s_now=0;s_now<=25;++s_now)
            if(val[i]==26||val[i]==s_now)
                for(int k=0;k<=25;++k)
                    if(val[i-1]==26||val[i-1]==k)
                    {
                        bool flag_s=expr(s_now),flag_k=expr(k);
                        if(flag_s==flag_k)
                            if(s_now==k)
                                for(int l=2;l<=C[flag_s];++l)
                                    for(int I=2;I<=E[flag_s];++I)
                                        dp[i][l][I][s_now]+=dp[i-1][l-1][I-1][k];
                            else
                                for(int l=2;l<=C[flag_s];++l)
                                    for(int I=1;I<=E[flag_s];++I)
                                        dp[i][l][1][s_now]+=dp[i-1][l-1][I][k];
                        else
                            for(int l=1;l<=C[flag_k];++l)
                                for(int I=1;I<=E[flag_k];++I)
                                    dp[i][1][1][s_now]+=dp[i-1][l][I][k];
                    }
    ll res=0;
    for(int i=0;i<=25;++i)
        if(val[len]==i||val[len]==26)
        {
            int flag_n=expr(i);
            for(int j=1;j<=C[flag_n];++j)
                for(int k=1;k<=E[flag_n];++k)
                    res+=dp[len][j][k][i];
        }
    printf("%lld",res);
    return 0;
}
/*
4 4 4 4
man****ipt
*/

```

贺题并不是一个好习惯呢。

### 另话

还有 $20$ 天就中考了，希望不要再改题解了，一遍过。也是时候学学同机房巨佬暂时 $AFO$ 一下了。七月再战吧！ $OI$ ！

推一波蒟蒻的[博客](https://violeteternal.github.io/Eternity/)

---

## 作者：Aurora_Borealis_ (赞：0)


# P6710 [BalticOI 2005] Ancient Manuscript题解
【解析】

~~看到题目先爆搜~~。

那就计算一下，假设字符串长度为 n，则字符串最多有 n 个空，每个空有 26 种可能，最劣复杂度可达 $ O(26^n) $，明显不可取。

而题目求方案数，搜索不行，那就 dp。

设 $ dp_{i,j,k,l} $ 表示前 i 位，连续相同字母 j 个，连续相同种类字母 k 个，当前字母为 l 的方案数。由于 i , j , k , l 的范围非常小，所以不用优化，直接无脑 dp。


稍微思考即可得出方程，由于过于繁琐，这里出示关键代码。

```
flag[0]=flag[4]=flag[8]=flag[14]=flag[20]=1;//把元音字母打上标记 
    for(int i=0;i<26;i++){//当前字符为26表示这个空需要填
    	if(a[1]==26||a[1]==i){
    	 	dp[1][1][1][i]=1;
		}
	}
    for(int i=2;i<=n;i++){
        for(int j=0;j<26;j++){
            if(a[i]==26||a[i]==j){
            	for(int k=0;k<26;k++){
                    if(a[i-1]==26||a[i-1]==k){
                        int p=flag[j],q=flag[k];
                        if(p==q){
                            if(j==k){
                            	for(int l=2;l<=c[p];l++){
                                    for(int iee=2;iee<=e[p];iee++){
                                        dp[i][l][iee][j]+=dp[i-1][l-1][iee-1][k];
                                    }
                                }
							}else{
								for(int l=2;l<=c[p];l++){
                                    for(int iee=1;iee<=e[p];iee++){
                                        dp[i][l][1][j]+=dp[i-1][l-1][iee][k];
                                    }
								}
							} 
                        }else{
                        	for(int l=1;l<=c[q];l++){
                                for(int iee=1;iee<=e[q];iee++){
                                    dp[i][1][1][j]+=dp[i-1][l][iee][k];
                                }
                            }
									}
                    }
                }
				}
        }
    }
    for(int i=0;i<26;i++){
    	if(a[n]==i||a[n]==26){
           int p=flag[i];
           for(int j=1;j<=c[p];j++){
            	for(int k=1;k<=e[p];k++){
            		ans+=dp[n][j][k][i];
					}
				}
       }
	}
   cout<<ans;
```

---

