# [ABC162D] RGB Triplets

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc162/tasks/abc162_d

`R`, `G`, `B` のみからなる、長さ $ N $ の文字列 $ S $ があります。

以下の $ 2 $ つの条件をともに満たす組 $ (i,~j,~k)~(1\ \leq\ i\ <\ j\ <\ k\ \leq\ N) $ の数を求めてください。

- $ S_i\ \neq\ S_j $ かつ $ S_i\ \neq\ S_k $ かつ $ S_j\ \neq\ S_k $ である
- $ j\ -\ i\ \neq\ k\ -\ j $ である

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 4000 $
- $ S $ は `R`, `G`, `B` のみからなる、長さ $ N $ の文字列である

### Sample Explanation 1

組 $ (1,~3,~4) $ だけが $ 2 $ つの条件をともに満たします。組 $ (2,~3,~4) $ は、$ 1 $ つ目の条件は満たしますが $ 2 $ つ目の条件を満たさないので不適です。

## 样例 #1

### 输入

```
4
RRGB```

### 输出

```
1```

## 样例 #2

### 输入

```
39
RBRBGRBGGBBRRGBBRRRBGGBRBGBRBGBRBBBGBBB```

### 输出

```
1800```

# 题解

## 作者：SpeedStar (赞：2)

### 算法分析
满足第一个条件的三元组的数量是$rgb$，其中$r$，$g$和$b$分别表示$S$中$R$，$G$，$B$的出现次数。现在，我们不妨考虑其中有多少个不满足第二个条件。注意到，使$j-i=k-j$的三元组$(i,j,k)$的数量为$O(N^2)$。 因此，我们可以通过固定$i$和$j$等方式遍历这些对象，然后检查其是否满足第一个条件。这个算法的时间复杂度为$O(N^2)$，其中后面的暴力为算法瓶颈。

### C++代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using ll = long long;
 
int n;
string s;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> s;
	
	ll r = count(begin(s), end(s), 'R');
	ll g = count(begin(s), end(s), 'G');
	ll b = count(begin(s), end(s), 'B');
	
	ll res = r * g * b;
	for (int j = 1; j < n; ++j) {
        for (int i = 0; i < j; ++i) {
			int k = 2 * j - i;
			if (k < n) res -= s[i] != s[j] and s[j] != s[k] and s[k] != s[i]; 
		}
	}
	
	cout << res << '\n';
	
	return 0;
}
```

---

## 作者：Andy_WA (赞：1)

这题没啥思路，直接暴力。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long len;
string str;
int main(){
	cin>>len>>str;
	long long r=count(str.begin(),str.end(),'R');//查找字母 "R" 的个数，格式见下详解 
	long long g=count(str.begin(),str.end(),'G');//查找字母 "G" 的个数，格式见下详解 
	long long b=count(str.begin(),str.end(),'B');//查找字母 "B" 的个数，格式见下详解 
	long long ans=r*g*b;//计算 ans 初始值 
	for(long long i=1;i<len;i++){
        for(long long j=0;j<i;j++){
			long long k=2*i-j;
			if(k<len && str[j]!=str[i] && str[i]!=str[k] && str[k]!=str[j]){//判断是否互不相等与边界，因为字符串 str 的下标是从 0 开始的，所以没有 str[len] 则 k 只用小于 len 就行了 
				ans--;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```
关于函数 `count()`，作用是数出一个字符串内的给定字母的出现次数，和以下语句基本等价：
```cpp
long long count(Begin,End,FindChir){
	for(long long i=Begin;i<End;i++){
		if(str[i]==FindChir){
			ans++;
		}
	}
	return ans;
}
```
只不过是把 `Begin` 和 `End` 换为了迭代器 $\tt{（iterator）}$ 而已。

标准写法见下：
```cpp
count(str.begin(),str.end(),FindChir);
```

最后，送大家一句话：
$$
\textit{\textbf{莫抄袭，棕了少年名，空悲切。}}
$$

---

## 作者：_Gabriel_ (赞：1)

### 思路

满足题目中第一个要满足的条件的三元组数量为 $cntr \times cntg \times cntb$（$cntr,cnrg,cntb$ 分别表示字符串 $S$ 中 $R,G,B$ 的个数），只要看有多少个三元组不满足题目中第二个要满足的条件，把它减掉即可。

枚举让 $j-i=k-j$ 的三元组数量，可以通过两重循环枚举 $i,j$，再特判这个三元组是否满足题目中第一个要满足的条件即可求出答案。

时间复杂度 $O(n^2)$

### 题解

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
string s;
int n;

int main() {
    cin >> n >> s;
    ll ans = (ll)count(s.begin(), s.end(), 'R') * count(s.begin(), s.end(), 'G') * count(s.begin(), s.end(), 'B');
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int k = j + (j - i);
            if (k >= n) continue;
            if (s[i] != s[j] && s[j] != s[k] && s[k] != s[i]) ans--;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：No21 (赞：1)

### 前言

本题中字符串只有 $R,B,G$ 三种字符。

### 解题思路

看到数据范围就应该考虑 $n^2$，毕竟只有 $4000$。

要求合法三元组数量，看起来很麻烦，那么我们换一种思路，当我们难以求出一个集合时，我们可以选择求它的补集，本题同理，我们可以先求出所有不合法的三元组，再用总的三元组数量（无论合法或不合法）减去不合法的三元组数量就得到了答案。

求总的三元组数量是简单的，我们只需要统计每种字符出现的次数然后将次数相乘即得到了总的三元组数量（无需证明，不会的手算一下，很简单）。

求不合法的三元组数量其实也不难（主要因为数据范围小），我们只要枚举距离，然后在字符串里查找就可以。

记得开 long long。

```
#include<bits/stdc++.h>
using namespace std;
namespace TO
{
    int n,r,g,b;
    long long ans;
    string s;
    int mian()
    {
        cin>>n>>s;
        for(int i=0;i<n;i++)
        {
            if(s[i]=='R')
                r++;
            if(s[i]=='G')
                g++;
            if(s[i]=='B')
                b++;
        }
        ans=1ll*r*g*b;
        for(int i=0;i<n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(i+j+j<n)
                {
                    if(s[i]!=s[i+j]&&s[i+j]!=s[i+j+j]&&s[i]!=s[i+j+j])
                        ans--;
                }
            }
        }
        cout<<ans;
        return 0;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return TO::mian();
}
```

---

## 作者：绿绵羊 (赞：1)

**注：本题解[博客界面](https://www.luogu.com.cn/blog/35153/solution-at4818)可以正常查看(虽然我也不知道是不是因为LaTeX而没过审的QwQ)**  
这道题还是值得说一说的。  
一开始，本蒟蒻想暴力枚举，然后一看数据……  
_(¦3」∠)_  
于是，我想到了优化。我们将每个$R$,$G$,$B$出现的位置分别记录下来，这样，每次选到的三个数就必定满足任两者间不重复，只用判断位置是否合法就行了。  
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin >> n;
	char ch;
	int a[n+1], b[n+1], c[n+1], s1=0, s2=0, s3=0;
	long long t=0;
	for (register int i=1; i<=n; i++)
	{
		cin >> ch;
		if (ch=='R')
		{
			s1++;
			a[s1]=i;
		}
		if (ch=='G')
		{
			s2++;
			b[s2]=i;
		}
		if (ch=='B')
		{
			s3++;
			c[s3]=i;
		}//分别记录出现的位置
	}
	for (register int i=1; i<=s1; i++)
		for (register int j=1; j<=s2; j++)
			for (register int h=1; h<=s3; h++)
			{
				int maxx=max(a[i], max(b[j], c[h])), minn=min(a[i], min(b[j], c[h]));
				double x=(maxx+minn)/2.0;
				if (x!=a[i]&&x!=b[j]&&x!=c[h]) t++;//判断位置是否合法，若合法，则累加
			 } 
	cout << t << endl;
	return 0;
}
```
于是，我飞速敲下了这一段代码，只用了20分钟（包括思考），结果……  
依然是一个大大的$\huge\text\color{White}\colorbox{Purple}{TLE}$（的确很大吧）。  
就超了200ms┭┮﹏┭┮  
~~严重怀疑是评测姬故障QwQ~~  
***
随后，我又想到了解决方法：将三重循环转成两重循环。  
可是，该怎么转呢？  
我们可以利用数学公式求出不判断位置的话能有多少个，再减掉那些因为位置不合法而不能算的，就能求出来总数。  
```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin >> n;
	char ch[n+1];
	int a[n+1], b[n+1], c[n+1], s1=0, s2=0, s3=0;
	long long t=0;
	for (register int i=1; i<=n; i++)
	{
		cin >> ch[i];
		if (ch[i]=='R')
		{
			s1++;
			a[s1]=i;
		}
		if (ch[i]=='G')
		{
			s2++;
			b[s2]=i;
		}
		if (ch[i]=='B')
		{
			s3++;
			c[s3]=i;
		}//分别记录出现的位置
	}
	for (register int i=1; i<=s1; i++)
		for (register int j=1; j<=s2; j++)
		{
			int maxx=max(a[i], b[j]), minn=min(a[i], b[j]);
			int dif=maxx-minn;
			t+=s3;//先将所有情况全部加上
			if (minn-dif>=1)
				if (ch[minn-dif]=='B') t--;
			if (maxx+dif<=n)
				if (ch[maxx+dif]=='B') t--;
			if (dif%2==0)
				if (ch[minn+dif/2]=='B') t--;//再减去不合法的情况
		} 
	cout << t << endl;
	return 0;
}
```
啊……终于$\color{white}\colorbox{green}{AC}$了……  
题解写得~~心~~好累……求通过`0=w=0`  

---

## 作者：GFyyx (赞：0)

### 审题与分析
给你一个字符串 $S$，你需要找到所有满足要求的三元组 $(i,j,k)(1 \le i \lt j \lt k \le N \le 4000)$。
其中 $S_i \neq S_j$，$S_j \neq S_k $，$S_i \neq S_k$，$j-i \neq k-j$。$N$ 是指 $S$ 中字符的个数。输出满足条件的三元组的个数。

数据范围在 $10^3$ 数量级的题目 $O(n^3)$ 暴力枚举所有三元组判断其合法性显然是会 TLE 的，考虑优化一重枚举。

### 解题思路
枚举 $i$ 和 $k$，如果 $S_i \neq S_k$ 则结果（设为 $ans$）增加区间 $[i,k]$ 中除 $S_i,S_k$ 外另一个字母的数量，再特判一下 $j-i=k-j$ 的情况即可。

$O(n^2)$ 枚举 $i$ 和 $k$，$O(1)$ 统计区间内合法 $j$ 的数量。
总时间复杂度为 $O(n^2)$。

### AC 代码（附有注释）
```cpp
#include <iostream>
#include <string>
using namespace std;
int r[4005],g[4005],b[4005];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n; cin >> n;
	string s; cin >> s;
	s="f"+s;//下标从1开始
	for(register int i=1; i<=n; i++){
		r[i]=r[i-1];g[i]=g[i-1];b[i]=b[i-1];
		if(s[i]=='R') r[i]++;
		if(s[i]=='G') g[i]++;
		if(s[i]=='B') b[i]++;
	}//统计[1,i]中每个字母的个数，便于快速查询 
	long long ans=0;
	for(register int i=1; i<n; i++){
		for(register int k=i+2; k<=n; k++){
			if(s[i]==s[k]) continue;
			if((s[i]=='R'&&s[k]=='G')||(s[i]=='G'&&s[k]=='R')){
				if(!((i+k)&1)&&s[(i+k)>>1]=='B') ans--;//判条件2 
				ans+=b[k]-b[i-1];
			}
			if((s[i]=='R'&&s[k]=='B')||(s[i]=='B'&&s[k]=='R')){
				if(!((i+k)&1)&&s[(i+k)>>1]=='G') ans--;//判条件2 
				ans+=g[k]-g[i-1];
			}
			if((s[i]=='B'&&s[k]=='G')||(s[i]=='G'&&s[k]=='B')){
				if(!((i+k)&1)&&s[(i+k)>>1]=='R')ans--;//判条件2 
				ans+=r[k]-r[i-1];
			}
		}
	}
	cout << ans << endl;//输出答案 
	return 0;
}
```

---

## 作者：沉石鱼惊旋 (赞：0)

[更好的阅读体验](http://blog.cyx2009.top/archives/187/)

# 题目翻译

> 有一个长度为 $n$，且只由 $\tt R,\tt G,\tt B$ 组成的字符串 $s$，求有多少个三元组 $(i,j,k)$ 满足：
> 
> - $1\leq i<j<k\leq n$。
> - $s_i\neq s_j,s_j\neq s_k,s_i\neq s_k$。
> - $j-i\neq k-j$。
> 
> $1\leq n \leq 4,000$。

# 题目思路

暴力枚举 $i,j,k$，但是 $\mathcal O(n^3)$ 超时。

考虑优化，我们枚举 $i,k$，可以通过前缀和预处理出这一段中 $s_j\neq s_i,s_j\neq s_k$ 的个数。

然后考虑性质 $j-i\neq k-j$，不难发现对于每一对 $(i,k)$，最多只有 $1$ 个 $j$ 使得 $j-i=k-j$，而且这个 $j=\frac{i+k}{2}$。

那么我们特判这一个特殊的 $j$ 即可。

时间复杂度 $\mathcal O(n^2)$，可以通过。

# 完整代码



```cpp
#include<bits/stdc++.h>
using namespace std;
int id(char c){if(c=='R')return 0;if(c=='G')return 1;return 2;}
int h[3][4020];
int n;
string s;
long long ans;
int main()
{
    cin>>n>>s;
    s=' '+s;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<3;j++)h[j][i]=h[j][i-1];
        h[id(s[i])][i]++;
    }
    for(int i=1;i<=n;i++)
    {
        for(int k=i+1;k<=n;k++)
        {
            if(s[i]==s[k])continue;
            int x=3-id(s[i])-id(s[k]);
            int tmp=h[x][k]-h[x][i-1];
            ans+=tmp;
            if(!(k+i&1)&&id(s[k+i>>1])==x)ans--;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```




---

## 作者：Hog_Dawa_IOI (赞：0)

前传：某天早上这道题被放进了我们的比赛里，我赛时只想到了暴力枚举三个数的算法，然而由于老师配置的数据太弱，我的代码居然过了……然而下午老师重测了一遍，100分秒变50分……

### 题意简述
给你一个长度为 $N$ 的、由 `R`，`G`，`B` 三个字母组成的字符串 $S$，求满足如下要求的三元组 $(i,j,k)$（$1 \le i < j < k \le N$）的个数：
- $S_i \neq S_j$ , $S_j \neq S_k $ , $S_i \neq S_k$
- $j-i \neq k-j$

数据范围是 $ 1\ \leq\ N\ \leq\ 4000 $。

### 思路分析
一开始大家一定会和我一样想到暴力枚举三个数的做法（时间复杂度为 $O(n^3)$），但显然这个算法会超时得让你等到花都谢了。所以我们需要优化我们的暴力。    
问题就出在这里：该如何优化呢？     
我们可以尝试忽略第二个条件，只求满足第一个条件的三元组的数量，再减去满足第一个条件而不满足第二个条件的三元组的数量，就是我们的答案。      
设三个字母出现的次数为 $r$，$g$，$b$，不难看出满足第一个条件的三元组的数量是 $r \times g \times b$。     
那么如何求满足第一个条件而不满足第二个条件的三元组（即在满足第一个条件的情况下，还满足 $j-i = k-j$）的数量呢？    
我们可以枚举 $k$ 和 $k - j$，继而可以求出 $j$ 和 $i$。接着我们判断这三个位置的字母是否互不相同，如果是，那么这个三元组就是满足第一个条件而不满足第二个条件的。    
这个算法只需要用到枚举 $k$ 和 $k - j$ 这两个变量的双重循环（比最开始的少了一层），时间复杂度为 $O(n^2)$，可以通过。   

### code展示
码风和大家可能有点不同，做了点解释，希望大家能看懂。
```cpp
#include<stdio.h>
int n;long long ans,sum1,sum2,sum3;char s[4005];
int main()
{
    scanf("%d%s",&n,s+1);//s+1为s数组的地址的起始位置往后一个位置，即输入的第一个字符会存进s[1]而不是s[0]中
    for(int i=1;i<=n;i++)//上文中的k
    {
        if(s[i]=='R') sum1++;
        if(s[i]=='G') sum2++;
        if(s[i]=='B') sum3++;
        for(int j=1;i-j*2>=1/*j为上文中的k-j*/;j++) if(s[i]^s[i-j]&&s[i-j]^s[i-2*j]&&s[i]^s[i-2*j]) ans--;
        //如果两个数不相等，那么这两个数异或的结果将大于0，即为真
    }
    printf("%lld",ans+sum1*sum2*sum3);
}
```

---

## 作者：zjc5 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_abc162_d)

**思路：**

首先可以想到暴力枚举 $i,j,k$，但是 $4000^3=64000000000$，肯定会超时。

所以可以用前缀和优化，分别统计 $R,G,B$ 的个数，然后枚举 $i,j$ 求出满足条件的 $k$ 的个数，并累加。

注意：前缀和统计的结果中可能包含 $j-i=k-j$ 这组解，需要减一。

代码时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans;
int n, k, rs[4010], gs[4010], bs[4010];
char ch[8010];//要开到8000以上，因为k会超过4000
int main() {
	cin >> n >> (ch + 1);
	for (int i = 1; i <= n; i++) {
		rs[i] = rs[i - 1];
		gs[i] = gs[i - 1];
		bs[i] = bs[i - 1];
		ch[i] == 'R' ? rs[i]++ : ch[i] == 'G' ? gs[i]++ : bs[i]++;
	}
	for (int i = 1; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (ch[i] != ch[j]) {
				k = j - i + j;
				if ('R' != ch[i] && 'R' != ch[j])
					ans += rs[n] - rs[j] - (ch[k] == 'R');
				else if ('G' != ch[i] && 'G' != ch[j])
					ans += gs[n] - gs[j] - (ch[k] == 'G');
				else
					ans += bs[n] - bs[j] - (ch[k] == 'B');
			}
	cout << ans;
	return 0;
}
```

---

## 作者：智子·起源 (赞：0)



### 题解·AT4818

### 难度评分：简单
  
  ----



### 1、理解题意

大意概括：

在一个只有RGB三种字符的字符串中有一些三个字符组成的一组东西满足：

1、三个字符中相邻两字符之间位置距离不相等

2、三个字符各不相同

现求该字符串中有多少组这样的东西。

----

### 2、明确思路

刚拿到手，当然是想到三for暴力，但

数据范围：n≤4000

**所以最多只能开两个for。**

**那我们的第三个for所寻找的字符其实可以用 _后缀和_ 来代替。**

代码结合：

原本的三for：

```cpp
for(int i=1;i<n-1;i++)
    for(int j=i+1;j<n;j++)
      for(int k=j+1;k<=n;k++)
	    if(s[i]!=s[j]&&s[j]!=s[k]&&s[i]!=s[k])ans++;
```

**优化后的双for：**

```cpp
  for(int i=1;i<n;i++)
    for(int j=i+1;j<=n;j++)
    {
      if(s[i]=='R'&&s[j]=='G')ans+=fb[j+1];
      if(s[i]=='R'&&s[j]=='B')ans+=fg[j+1];
      if(s[i]=='G'&&s[j]=='R')ans+=fb[j+1];
      if(s[i]=='G'&&s[j]=='B')ans+=fr[j+1];
      if(s[i]=='B'&&s[j]=='R')ans+=fg[j+1];
      if(s[i]=='B'&&s[j]=='G')ans+=fr[j+1];
	}//虽然看上去挺多的，但其实思路很简单——ans实行的加法操作多了一个维度。（0维->1维）
```

看到这里，肯定有人要跳过了，但我们还有第二个问题：

`    三个字符中相邻两字符之间位置距离不相等
————前文`


**所以，我们还要对get到的ans实行“减脂”处理——即减掉三个字符位置距离相等且三个字符互不相等的情况。**

具体代码：

```cpp
  for(int i=1;i<n;i++)
    for(int j=1;j<=n;j++)
    {
      if(i+j+j>n||i+j>n)continue;
      if(s[i]!=s[i+j]&&s[i+j]!=s[i+j+j]&&s[i]!=s[i+j+j])ans--;
	}
```



----

### 3、“Talking is cheap，so let me show you the code！”

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans,fr[4000+5],fg[4000+5],fb[4000+5];
string s;
int main()
{
  cin>>n>>s;
  s=' '+s;
  for(int i=n;i>0;i--)
  {
  	fr[i]=fr[i+1],fg[i]=fg[i+1],fb[i]=fb[i+1];
    if(s[i]=='R')fr[i]++;
    if(s[i]=='G')fg[i]++;
    if(s[i]=='B')fb[i]++;
  }
  for(int i=1;i<n;i++)
    for(int j=i+1;j<=n;j++)
    {
      if(s[i]=='R'&&s[j]=='G')ans+=fb[j+1];
      if(s[i]=='R'&&s[j]=='B')ans+=fg[j+1];
      if(s[i]=='G'&&s[j]=='R')ans+=fb[j+1];
      if(s[i]=='G'&&s[j]=='B')ans+=fr[j+1];
      if(s[i]=='B'&&s[j]=='R')ans+=fg[j+1];
      if(s[i]=='B'&&s[j]=='G')ans+=fr[j+1];
	}
  for(int i=1;i<n;i++)
    for(int j=1;j<=n;j++)
    {
      if(i+j+j>n||i+j>n)continue;//别忘了越界问题
      if(s[i]!=s[i+j]&&s[i+j]!=s[i+j+j]&&s[i]!=s[i+j+j])ans--;
	}
  printf("%lld\n",ans);//别忘换行！！！
	return 0;
}

```

### 抄袭可耻，后果自负。
---

### 文末

致可爱的管理员：

好久没发题解了，为了我的咕值，过一下吧，谢谢~QWQ~

---

## 作者：litluo (赞：0)

# RGB Triplets

~~广告：在博客园食用更佳~~ <https://www.cnblogs.com/louyj/p/ABC162D.html>

题目大意：有一个长度为 $n$ 的字符串 $s$，只包含字符 `R` `G` `B`，找出满足以下两个条件的三元组 $(i, j, k)$ $(1\le i<j<k \le n)$：

> 1. $s_i \neq s_j$ ，$s_i \neq s_k$，$s_j \neq s_k$。
> 1. $j - i \neq k - j$

首先 $O(n^3)$ 的大暴力是过不了的＞︿＜

所以要优化到 $O(n^2)$

因为我们要得到三个字母不同的子序列，所以可以直接考虑用乘法原理。之后再进行遍历把满足 $j - i = k - j$ 的情况去掉即可，后期遍历方式如下图：

$j \ \xrightarrow{i} \ j + i+ 1  \xrightarrow{i} \ j + 2 \times i + 2$

我们从第 $j$ 个字符开始，向后扩展 $i$ 个字符，得到第 $j + i + 1$ 个字符。在此基础上，再向后扩展 $i$ 个字符，得到第 $j + 2 \times i + 2$ 个字符。则这三个字符不满足条件二，如果这三个字符满足 `RGB` 各有一个，那么就要在 $ans$ 中减去 $1$，因为虽然这三个字符不满足条件二，但因乘法原理算进了 $ans$ 中。其中 $i$ 由于三个相邻的不同字符也不满足条件二，所以 $0 \le i \le \left\lfloor\dfrac{n - 3}{2}\right\rfloor$，而 $j$ 满足 $j \ge 1 \And j + i \times 2 + 2 \le n$。

就直接看代码了：

```cpp
#include <bits/stdc++.h>
using namespace std;

inline long long read(){    //快读
    long long s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9'){
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9'){
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * w;
}
long long n, r, g, b;
unsigned long long ans; //usnigned 用不用好像都无所谓……
char s[4040];           //千万不能用string，不然会炸掉
int main(){
    n = read();
    for (int i = 1; i <= n; i++){
        s[i] = getchar();
        if (s[i] == 'R') r++;    //对r, g, b计算一个初始值，方便使用乘法原理
        if (s[i] == 'G') g++;
        if (s[i] == 'B') b++;
    }
    ans = r * g * b;  //乘法原理预处理ans，但多出来很多的不符合条件的答案
    int _n = (n - 3) >> 1;  //计算(n-3)/2
    for (int i = 0; i <= _n; i++){  //枚举两个字符之间的差
        for (int j = 1; j + 2 * i + 2 <= n; j++){  //枚举j的大小
            if (s[j] != s[j+i+1] && s[j] != s[j+i*2+2] && s[j+i+1] != s[j+i*2+2]){  //如果满足条件1，就将ans--
                ans--;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：do_while_true (赞：0)

如果没有 $j-i\ne k-j$ 的限制，我们很容易看出来答案就是 "R"的个数 $*$ "G"个数 $*$ "B"的个数。

那么对于一个结束点 $k$ ，我们去枚举一个 $x$ 作为 $j-i$ 和 $k-j$ ，也就是他们之间的距离。如果枚举到的 $s_j$ 和 $s_k$ 以及当前的 $s_i$ 正好可以组成 "R","G","B"，我们就把答案减去一个，因为这组不满足最后一个限制。

## $\mathcal{Code:}$

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n;
char ch[4001];
long long sum1,sum2,sum3,ans;
int main()
{
	scanf("%d\n",&n);
	for(int i=1;i<=n;i++){
		scanf("%c",&ch[i]);
		if(ch[i]=='R') sum1++;
		if(ch[i]=='G') sum2++;
		if(ch[i]=='B') sum3++;
		for(int j=1;j*2+1<=i;j++)
			if(ch[i]!=ch[i-j]&&ch[i]!=ch[i-2*j]&&ch[i-j]!=ch[i-2*j]) ans--;
	}
	ans+=sum1*sum2*sum3;
	printf("%lld",ans);
}
```


---

## 作者：1n1c5c5z (赞：0)

## 题目大意：
给定长度为 $N$ 字符串 $s$，由 $R,G,B$ 三种字符组成，求三元组 $(i,j,k)(1 \leq i \leq j \leq k \leq N)$ 的个数使其满足：
- $s_i \neq s_j,s_i \neq s_k,s_j \neq s_k$
- $j-i \neq k-j$

## Solution:
法一：  
暴力 $O(n^3)$ 枚举。  
由于 $N \leq 4000$，肯定会超时。  
法二：  
考虑后缀和，令 $RGB_{i,0},RGB_{i,1},RGB_{i,2}$ 分别为 $s$ 的第 $i$ 个字符到最后的 $R,G,B$ 字符数量。  
然后 $O(n^2)$ 枚举三元组的前两个元素，再加上后面剩余元素的数量，最后特判不满足第二个条件的情况。
## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int RGB[4005][3];//后缀和数组
string s;
int main()
{
    long long n,ans=0;
    cin>>n>>s;
	RGB[n][0]=0;
	RGB[n][1]=0;
	RGB[n][2]=0;
	for(int i=n-1;i>=0;i--)
	{
		RGB[i][0]=RGB[i+1][0];//预处理后缀和
		RGB[i][1]=RGB[i+1][1];
		RGB[i][2]=RGB[i+1][2];
		if (s[i]=='R')RGB[i][0]++;
		else if (s[i]=='G')RGB[i][1]++;
		else if (s[i]=='B')RGB[i][2]++;
	}
    for(int i=0;i<n;i++)//二重循环枚举前两个元素
    {
    	for(int j=0;j<i;j++)
    	{//依次处理6种情况
    		if (s[j]=='R' && s[i]=='G')//差B字符
    		{
    			ans+=RGB[i+1][2];
    			if (s[2*i-j]=='B')ans--;//特判(前文已提到)如果(i,j,2*i-j)也满足第一个条件，答案要减一
			}
			else if (s[j]=='R' && s[i]=='B')//差G字符
    		{
    			ans+=RGB[i+1][1];
    			if (s[2*i-j]=='G')ans--;
			}
			else if (s[j]=='G' && s[i]=='R')//差B字符
    		{
    			ans+=RGB[i+1][2];
    			if (s[2*i-j]=='B')ans--;
			}
			else if (s[j]=='G' && s[i]=='B')//差R字符
    		{
    			ans+=RGB[i+1][0];
    			if (s[2*i-j]=='R')ans--;
			}
			else if (s[j]=='B' && s[i]=='R')//差G字符
    		{
    			ans+=RGB[i+1][1];
    			if (s[2*i-j]=='G')ans--;
			}
			else if (s[j]=='B' && s[i]=='G')//差R字符
    		{
    			ans+=RGB[i+1][0];
    			if (s[2*i-j]=='R')ans--;
			}
		}
	}
	cout<<ans<<endl;
}

```

---

## 作者：AmamiyaYuuko (赞：0)

考虑先求出所有满足 $s_i \neq s_j, s_j \neq s_k, s_k \neq s_i$ 的三元组个数。设三种字母出现的个数分别为 $r, g, b$，不难发现这个东西就是 $r \times g \times b$。

然后再减掉不满足条件 2 的情况。

$j - i \neq k - j$，这句话其实就是说明从 $i$ 到 $j$ 和从 $j$ 到 $k$ 的距离相等，所以我们可以枚举长度和 $i$ 来达到这个目的，在枚举的时候减掉只满足条件 1 的情况即可。

具体实现可以看代码。

```cpp
int main() {
    read(n);    std::cin >> s + 1;
    for (int i = 1; i <= n; ++i) {
        if (s[i] == 'R')    ++r;
        if (s[i] == 'B')    ++b;
        if (s[i] == 'G')    ++g;
    }
    ans = r * b * g;
    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i <= n; ++i) {
            int j = i + len, k = i + len + len;
            if (k > n)  break;
            if (s[i] != s[j] && s[i] != s[k] && s[j] != s[k])   --ans;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

别忘了开 long long。

---

