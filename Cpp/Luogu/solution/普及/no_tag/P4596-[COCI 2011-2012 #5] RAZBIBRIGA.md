# [COCI 2011/2012 #5] RAZBIBRIGA

## 题目描述

四个长度相同的单词可以拼成一个正方形，如下图，`"HLAD","NIVA","HSIN","DEDA"` 拼成了一个 $4\times 4$ 的正方形。

![](https://cdn.luogu.com.cn/upload/image_hosting/7i3lhwgv.png)

现在给你 $N$ 个等长的单词，求这些单词的子集可以拼成多少个不同的正方形，输出方案数。

注意，**同一方格内不能有重复的单词**，如果两个单词至少有一个字符不同，那这两个单词就是不同的。

## 说明/提示

$4\le N\le 10^{5}$。

每个单词至多有 $10$ 个字符。

单词由大写字母构成。

题目译自 [COCI 2011/2012 #5 T4](https://hsin.hr/coci/archive/2011_2012/contest5_tasks.pdf)。

## 样例 #1

### 输入

```
4
NIVA
HLAD
HSIN
DEDA
```

### 输出

```
2```

## 样例 #2

### 输入

```
6
BAKA
BARA
BALC
CALC
ARHC
BLIC
```

### 输出

```
8```

# 题解

## 作者：ccsc (赞：8)

本题……

奥义！---真！！---暴力！！！

意题目中的限制条件，保证单词均不相同，所以不用担心重复单词的情况。

　　那么组成正方形就只与首尾字母有关，于是我们开一个二维的桶记录每个首尾搭配出现的次数。

　　然后枚举3条边的情况，就能确定第4条边，累乘次数统计答案，而为了防止同一单词重复用，每次枚举一种首尾搭配后，该种搭配就-1，枚举完再补回来就好了。

　　时间复杂度O(ac)
  
  code：
  
  ```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
const int M=26;
ll cnt[M][M],n;
char s[M];
ll ans;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s);
		cnt[s[0]-'A'][s[strlen(s)-1]-'A']++;
	}
	for(int i=0;i<26;i++){
		for(int j=0;j<26;j++){
			ll t1=cnt[i][j];cnt[i][j]--;
			for(int k=0;k<26;k++){
				ll t2=cnt[i][k];cnt[i][k]--;
				for(int w=0;w<26;w++){
					ll t3=cnt[j][w];cnt[j][w]--;
					ll t4=cnt[k][w];
					ans+=t1*t2*t3*t4;
					cnt[j][w]++;
				}
				cnt[i][k]++;
			}
			cnt[i][j]++;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：_zexal_ (赞：1)

## 思路
题目写道 $ N $ 个等长的单词，所以我们其实只需用桶记录每一个单词的头和尾即可。由于只有 26 个大写英文字母，所以我们只需枚举字母，看他们组成的边是否合法即可。至于字母可能重复问题，我们只需要每次枚举时减去那一个点，后面维护即可。
## 坑点
题目有一个隐形条件没有说，单词组成的正方形需要一定的顺序，**单词需从上往下，从左往右**。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long c[27][27];
string s;
int n;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		c[s[0]-'A'+1][s[s.size()-1]-'A'+1]++;	
	}
	long long sum=0,l1,l2,l3,l4;
	for(int i=1;i<=26;i++)
	{
		for(int j=1;j<=26;j++)
		{
			l1=c[i][j];c[i][j]--;//去重
			for(int k=1;k<=26;k++)
			{
				l2=c[i][k];c[i][k]--;
				for(int l=1;l<=26;l++){
					l3=c[j][l];
					c[j][l]--;
					l4=c[k][l];
					sum+=l1*l2*l3*l4;
					c[j][l]++;
				}
				c[i][k]++;
			}
			c[i][j]++;//维护
		}
	}
	cout<<sum;
	return 0;
}
```



---

## 作者：yeshubo_qwq (赞：1)

## 思路
因为一个单词只有头和尾会在顶点上重叠，所以按单词的头和尾计数。

然后，枚举四个顶点上的字母，判断方案是否可行。

如果可行，根据乘法原理累加答案即可。

注意：可能会出现需要两个同头同尾的单词，所以要防止单词重复用。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long//不开LL见祖宗 
using namespace std;
int n,i,j,k,l,a,b,c,ans,v[26][26];
char s[11];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>s;
		v[s[0]-'A'][s[strlen(s)-1]-'A']++;//按单词的头和尾计数 
	}
	for(i=0;i<26;i++)
		for(j=0;j<26;j++) 
			if(v[i][j]>0){//存在符合单词 
				a=v[i][j];
				v[i][j]--;//防止单词重复用 
				for(k=0;k<26;k++)
					if(v[i][k]>0){
						b=v[i][k];
						v[i][k]--;
						for(l=0;l<26;l++)
							if(v[k][l]>0){
								c=v[k][l];
								v[k][l]--;
								if(v[j][l]>0)
									ans+=v[j][l]*a*b*c;//累加答案 
								v[k][l]++;
							}
						v[i][k]++;
					}
				v[i][j]++;//还原 
			}
	return cout<<ans,0;
}
```


---

## 作者：XL4453 (赞：1)

坑点有点多的暴力题。



------------
解题思路：

观察本题，可以发现其实所有的首尾相同的单词都是“等价的”，在本题的要求中，其实并不在乎中间的字母。

由此想到可以用一个二维桶来记录所有“相同的”单词，然后枚举四个顶点的单词并往里面填。

时间复杂度为 $O(1)$ ，是常数级的，这一点另一篇题解写得有些问题。

正如开头所说，这题有很多坑点，现列举如下：

1. 读词的顺序

	原文中是这样说的：
    
    		水平单词只能从左往右读，竖直的单词只能从上往下读。四个角共用一个字母。 
    
    这就意味着在代码中必须严格数组的顺序。
    
2. “重复的词”

	原文中写到：
    
    	一个方案中不允许有同一个单词，两个方案不同是指它们所构成的正方形至少有一个字母不同。
    
    这也就意味着当有几条边中首位字母一样时会有词重复计算，这里可以用减去的方法来完善算法。
    
3. 其他
	
    在代码中提到
    


------------
代码：

```cpp
#include<cstring>
#include<cstdio>
using namespace std;
int h[30][30],n;
long long ans;
char a[100000];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",a);
		h[a[0]-'A'][a[strlen(a)-1]-'A']++;
		//注意是大写的 
	}
	int k1,k2,k3,k4;
	for(int i=0;i<26;i++){
		for(int j=0;j<26;j++){
			k1=h[i][j];h[i][j]--;
			for(int k=0;k<26;k++){
				k2=h[j][k];h[j][k]--;
				for(int l=0;l<26;l++){
					/*这里有一个大坑 
					读英文单词全都是从上往下，从左往右的
					不可以写成(i,j)(j,k)(k,l)(l,i) 
					*/
					k3=h[l][k];h[l][k]--;
					k4=h[i][l];
					ans+=k1*k2*k3*k4;
					h[l][k]++;
				}
				h[j][k]++;
			}
			h[i][j]++;
		}
	}
	printf("%lld\n",ans);
	//注意long long 
	return 0;
}
```

    

---

## 作者：skyskyCCC (赞：0)

## 前言。
较为简单的模拟，需要一点点的思维技巧与读题能力。
## 分析。
其实我们对于这 $n$ 个字符串，不需要考虑每一个字符，因为只需要将它们首尾相连构成一个正方形即可。所以我们只需要记录一下每一个字符串的头和尾即可，同时我们也需要记录它们的使用情况，所以我们可以开一个桶来完成这一个操作。

需要注意的是，因为我们要寻找合法方案，所以我们在模拟方案时，要先标记该桶已经使用，每次找到一个方案后，我们要将**已经标记**的桶还原，通过这一个操作，我们就既可以重复利用一个字母，也可以完美地解决同一方格内不能有重复的单词的要求。

因为有 $26$ 个大写字母，而数据范围又很小，所以我们可以直接枚举每个字母，然后判断每个方案是否合理即可。

但是翻译中漏掉了最重要的一点：水平的单词只能从左往右读，竖直的单词只能从上往下读。所以这就对方案有了一个顺序限制。

代码如下，仅供参考：
```
#include<iostream>
#include<cstring>
using namespace std;
long long n,last_ans,k,l,r,q,ans[30][30];
string s;
int main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>s;
		ans[s[0]-'A'+1][s[s.size()-1]-'A'+1]++;//桶
	}
	for (int i=1;i<=26;i++){
		for (int j=1;j<=26;j++){
			k=ans[i][j];
			ans[i][j]--;//标记。
			for (int k2=1;k2<=26;k2++){
				l=ans[i][k2];
				ans[i][k2]--;
				for (int k3=1;k3<=26;k3++){
					r=ans[j][k3];
					ans[j][k3]--;
					q=ans[k2][k3];
					last_ans+=k*l*r*q;
					ans[j][k3]++;//还原。
				}
				ans[i][k2]++;//还原。
			}
			ans[i][j]++;//还原。
		}
	}
	cout<<last_ans<<"\n";
	return 0;
}
```
## 后记。
此题代码细节较多，尤其是四重循环内的变量变换，不要和我一样因为把 $i$ 写成 $j$ 调了近半小时。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Genius_Star (赞：0)

### 思路：
本题其实很水，直接暴力枚举就好了。

注意题目中的限制条件，保证单词均不相同，所以不用担心重复单词的情况。

那么组成正方形就只与首尾字母有关，于是我们开一个二维的桶记录每个首尾搭配出现的次数。

然后枚举 $3$ 条边的情况，就能确定第 $4$ 条边，累乘次数统计答案，而为了防止同一单词重复用，每次枚举一种首尾搭配后，该种搭配就 $-1$，枚举完再补回来就好了。

时间复杂度 $O(26^4)$。
### 完整代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define RE register
#define For(i,a,b) for(RE int (i)=(a);(i)<=(b);(i)++)
using namespace std;
int n,cnt[26][26];
ll ans;
char s[15];

int main(){
    scanf("%d",&n);
    For(i,1,n) scanf("%s",s),cnt[s[0]-'A'][s[strlen(s)-1]-'A']++;
    For(lup,0,25) For(rup,0,25) {
        int t1=cnt[lup][rup]--,t2,t3;
        For(ldo,0,25){
            t2=cnt[lup][ldo]--;
            For(rdo,0,25){
                t3=cnt[rup][rdo]--;
                ans+=(ll)cnt[ldo][rdo]*t1*t2*t3;
                cnt[rup][rdo]++;
            }
            cnt[lup][ldo]++;
        }
        cnt[lup][rup]++;
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：Kevin_Mamba (赞：0)

### 题意

略。

### 解析

对于每个单词，你发现只有单词的**开头和结尾字母**有用，于是开一个桶，$a_{i,j}$ 表示以 $i$ 开头，$j$ 结尾的单词的数目。

随即**暴力枚举矩形四个顶点的字母**，将数量乘起来。注意可能会重复，需要边乘边删。具体实现见代码。

时间复杂度：${O({|\Sigma|}^4)}$，空间复杂度：${O({|\Sigma|}^2)}$，${|\Sigma|}$ 为字符集 $(A\sim Z)$ 大小。

### 代码

```cpp
#include<bits/stdc++.h>
#define il inline
#define re register
using namespace std;

int n,a[29][29],b[8];

char s[16];

long long ans;

il void gao() {
	long long ret=1;
	ret*=a[b[1]][b[2]];
	a[b[1]][b[2]]--;
	ret*=a[b[1]][b[3]];
	a[b[1]][b[3]]--;
	ret*=a[b[2]][b[4]];
	a[b[2]][b[4]]--;
	ret*=a[b[3]][b[4]];
	ans+=ret;
	a[b[1]][b[2]]++;
	a[b[1]][b[3]]++;
	a[b[2]][b[4]]++;	
}
 
il void dfs(re int level) {
	if(level>4) {
		gao();
		return ;
	}
	for(re int i=0;i<26;i++) {
		b[level]=i;
		dfs(level+1);
	}
}

int main() {
	scanf("%d",&n);
	for(re int i=1;i<=n;i++) {
		scanf("%s",s);
		a[s[0]-'A'][s[strlen(s)-1]-'A']++;
	}
	dfs(1);
	printf("%lld\n",ans);
	return 0;
}
/*
4
NIVA
HLAD 
HSIN 
DEDA

6 
BAKA 
BARA 
BALC 
CALC 
ARHC 
BLIC
*/
```

---

