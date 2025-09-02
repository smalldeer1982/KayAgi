# 愉快なロゴデザイン

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2015/tasks/joisc2015_b



# 题解

## 作者：AC_love (赞：1)

环不好处理，我们考虑破环成链。

破环成链后，枚举起点，求一下有多少要改的字符即可。

直接扫过去复杂度太高，可以使用前缀和优化。

[code](https://atcoder.jp/contests/joisc2015/submissions/59719806)

---

## 作者：Supor__Shoep (赞：1)

当我们看到题目的时候，我们就不难发现这道题可以进行暴力处理。当我们 $O(4^k)$ 枚举每一个字符作为开头，然后再循环 $k$ 次暴力计算，就可以得到正确答案。

具体做法就是先**破环成链**，把一个环拆成一个 $4^k\times 2$ 的数组。然后再枚举每一个开头，这里我使用的是递归，我们可以打一个 $4^k$ 的表，然后用前缀和计算当前需要修改的字符数量，进行累加，然后递归 $k-1$ 时的答案。

代码也是非常简短：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3e6+5;
int n;
int sum1[MAXN],sum2[MAXN],sum3[MAXN];
char s[MAXN];
int db[15]={0,1,4,16,64,256,1024,4096,16384,65536,262144,1048576};
int find(int x,int y)
{
	if(!y)	return 0;
	return abs(db[y]-sum1[x+db[y]-1]+sum1[x-1])+abs(db[y]-sum2[x+db[y]*2-1]+sum2[x+db[y]-1])+abs(db[y]-sum3[x+db[y]*3-1]+sum3[x+db[y]*2-1])+find(x+db[y]*3,y-1);
}
int main()
{
	cin>>n>>(s+1);
	int len=strlen(s+1);
	for(int i=1;i<=len;i++)	s[i+len]=s[i];
	for(int i=1;i<=len*2;i++)	sum1[i]=sum1[i-1]+(s[i]=='J'),sum2[i]=sum2[i-1]+(s[i]=='O'),sum3[i]=sum3[i-1]+(s[i]=='I');
	int res=1e9;
	for(int i=1;i<=len;i++)	res=min(res,find(i,n));
	cout<<res<<endl;
	return 0;
}
```

---

## 作者：Nickle (赞：1)

## 题目简述：

定义一个 $0$ 阶序列为“J，O，I”中的任意一个字母。定义k阶序列为 $4^{k-1}$ 个‘J’， $4^{k-1}$ 个‘O’， $4^{k-1}$ 个‘I’在最后接上 $(k-1)$ 阶序列。   

如：$1$ 阶序列可以是：‘JOII’；$2$ 阶序列可以是：‘JJJJOOOOIIIIJOII’。   

给定一个长度为 $4^{k-1}$ 的环状字符串，求最少修改多少次可以使该序列变为上述k阶序列。

## 思路：

类似于模拟的做法。

首先会想到纯暴力的做法：枚举每一个开头位置，暴力统计答案。

优化暴力统计答案的部分：

预处理出给出的字符串的‘J’，‘O’，‘I’ 的数量前缀和。

枚举每个位置，把该位置认为成序列的开头，利用前缀和快速计算出需要修改的数量。复杂度为 $\text{O}{(k\times 4^{k})}$。

## 代码以及代码解释：

* 变量： 

$qj$ 为‘J’的前缀和， $qo$ 为‘O’的前缀和， $qi$ 为‘I’的前缀和， $n4$ 用来存储 $4$ 的 $k$ 次幂。

$l$ 为一串 ‘JJJJJJ……’ 或者 ‘OOOOOOO……’ 或者 ‘IIIIIII……’ 的左端点， $r$ 为右端点。

* 函数：

 smf函数：由于我的前缀和从0开始记录。那么区间为 $[ 0 , r ]$ 的时候，作差会出现： $l-1=0-1=-1$ 。为了防止出错，特判该情况。

* 对于 $l$ 与 $r$ 的处理：

 可以选择二倍字符串或者计算对应位置来得到正确答案。这里我选择了后者。

完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e6+105;
int k,qj[N],qo[N],qi[N];
string c,s;
int n4[11]={1,4,16,64,256,1024,4096,16384,65536,262144,1048576};
inline int smf(int x,int cnt){
	if(cnt==1){
        if(x==-1) return 0;
        else return qj[x];
    }
	else if(cnt==2){
        if(x==-1) return 0;
        else return qo[x];
    }   
	else if(cnt==3){
        if(x==-1) return 0;
        else return qi[x];
    }     
}
int main(){
    cin>>k;cin>>c;
    s=c;s=s+c;
    if(s[0]=='J') qj[0]=1;
    else if(s[0]=='O') qo[0]=1;
    else if(s[0]=='I') qi[0]=1;
    for(int i=1;i<n4[k];i++){
        if(s[i]=='J') qj[i]=qj[i-1]+1,qo[i]=qo[i-1],qi[i]=qi[i-1];
        else if(s[i]=='O') qo[i]=qo[i-1]+1,qj[i]=qj[i-1],qi[i]=qi[i-1];
        else if(s[i]=='I') qi[i]=qi[i-1]+1,qo[i]=qo[i-1],qj[i]=qj[i-1];
    }
    int ans=N;
    int len;
    for(int i=0;i<n4[k];i++){
        int res=0,pos=i;int l=pos;int r;
        for(int j=k;j>=1;j--){       
            len=n4[j-1];r=l+len-1;           
            for(int p=1;p<=3;p++){
                int val=0;               
                if(r>=n4[k] && l<n4[k])			
                    val+=( smf(n4[k]-1,p)-smf(l-1,p)) + (smf(r-n4[k],p) );           	
                else if(l>=n4[k] && r>=n4[k])
                	 val+=( smf(r-n4[k],p) - smf(l-n4[k]-1,p) );				                 
                else val+=( smf(r,p)-smf(l-1,p) );               									  
                res+=(len-val);   
				l+=len;r=l+len-1; 
            }       			  
        }
        ans=min(ans,res);
    }
    printf("%d\n",ans);
	return 0;
}



```

---

## 作者：XYY1411 (赞：1)

# 愉快なロゴデザイン

提交地址：[洛谷 AT1250](https://www.luogu.com.cn/problem/AT1250)，[
AtCoder AT1250](https://atcoder.jp/contests/joisc2015/tasks/joisc2015_b)

## 题目大意

给出 $K$ 与长度为 $4^K$ 的字符串，现要替换一些字符，使其从环上某位置开始顺时针读取这个字符环，能得到一个 $K$ 级 JOI 序列，要求最小化替换字符数。

$K + 1$ 阶 JOI 序列分为四段：

- 前 $4^K$ 个字符全为 `J`。
- 然后 $4^K$ 个字符全为 `O`。
- 然后 $4^K$ 个字符全为 `I`。
- 最后 $4^K$ 个字符为 $K$ 阶 JOI 序列。

## 分析

看数据范围，$k \le 10$，当 $k = 10$ 时 $2^k = 1024$，我们考虑暴力枚举起始点，然后前 $\frac{3}{4}$ 和后 $\frac{1}{4}$ 分开处理，前面部份可以前缀和预处理，$O(1)$ 查询，后面部分递归查询。

由于字符串是个环，断环成链直接复制一倍，记得开两倍空间。

复杂度是 $O(4^K \times K)$。

## $\rm \color{green}code$

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>
using namespace std;
const int maxn = (1 << 20) + 5;
int k, n;
char s[maxn << 1];
int prej[maxn << 1], preo[maxn << 1], prei[maxn << 1];
int ans = INT_MAX, res;
auto query(int pre[], int l, int r) {
    return pre[r] - pre[l - 1];
};
void work(int l, int r) {
    if (l == r) return;
    int len = (r - l + 1) >> 2;
    res += len - query(prej, l, l + len - 1);
    res += len - query(preo, l + len, l + len * 2 - 1);
    res += len - query(prei, l + len * 2, l + len * 3 - 1);
    work(l + len * 3, r);
}
int main() {
    scanf("%d%s", &k, s + 1);
    n = 1 << (k << 1);
    strncpy(s + 1 + n, s + 1, n), s[n + n + 1] = '\0';
    for (int i = 1, lim = n << 1; i <= lim; ++i) {
        prej[i] = prej[i - 1] + (s[i] == 'J');
        preo[i] = preo[i - 1] + (s[i] == 'O');
        prei[i] = prei[i - 1] + (s[i] == 'I');
    }
    for (int i = 1; i <= n; ++i) {
        res = 0;
        work(i, n + i - 1);
        ans = min(res, ans);
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：da32s1da (赞：1)

```
T2愉快的logo设计题解
算法一：
我们很容易发现，实际上一个合法的字符串大多数字符都是固定好了的，而只有一个字符是任意的；
那么处理出合法的字符串，然后枚举环上每一个可能开始读的位置，暴力计算不匹配的个数，取最小值为答案即可；
时间复杂度O((4^n)^2)；
算法二：
考虑优化算法一，我们每一次做一次匹配的代价太大了；
因为题中的合法串有很长一段的连续相同字符，那么经过一次右移之后，有些地方匹配的字母是相同的，不用重复计算；
而必须要计算的是每一段’J’，’O’，’I’的首位，这些位置的个数只有n的级别，直接暴力处理就可以了；
时间复杂度O(4^n+(4^n)*n)=O(n*4^n)；
```

---

## 作者：Red_river (赞：0)

### 题目大意
这道题也是非常的水，但是就是细节有一点点多。并且在输出的时候记得加换行，问就是特性。题目大意为： $S_{k+1}$ 为每个 $4^k$ 个字符三个字符，最后 $4^k$ 个字符是字符串 $S_k$。
### 题意分析
先看看数据范围，也是非常小，时间复杂度是 $O(n^2)$ 的都能过。考虑暴力枚举起点，再接着每次循环判断。可以拿前缀和来优化。时间复杂度是 $O(nk)$ 的。具体可以参考代码及注释理解。

### CODE

```cpp
#include<bits/stdc++.h>
#define wk(x) write(x),putchar(' ')
#define wh(x) write(x),putchar('\n')
#define int long long
#define ull unsigned long long
#define ri register int
#define INF 2147483647
#define mod 998244353
#define N 2000000
#define NO printf("No\n")
#define YES printf("Yes\n")
#define f(x,k,y) for(int x=k;x<=y;x++)
using namespace std;
int n,m,k,jk,ans,sum,num,cnt,tot;
int dis[N][4],vis[N],wis[N],f[N];
char a[N];

inline void read(int &x){
	x=0;int ff=1;char ty;
	ty=getchar();
	while(!(ty>='0'&&ty<='9'))
	{
		if(ty=='-') ff=-1;
		ty=getchar();
	}
	while(ty>='0'&&ty<='9')
		x=(x<<3)+(x<<1)+ty-'0',ty=getchar();
	x*=ff;return;
}

inline void write(int x){
	if(x<0){
		x=-x;putchar('-');
	}if(x>=10) write(x/10);
	putchar('0'+x%10);
	return;
}

int ksm(int x,int y){
	int z=1;while(y>0){
		if(y&1) z*=x;
		x*=x;y>>=1;
	}return z;
}

signed main()
{
//	freopen("logo.in","r",stdin);
//	freopen("logo.out","w",stdout);
	read(n);scanf("%s",a+1);m=strlen(a+1);
	for(int i=1;i<=m;i++){
		dis[i][1]=dis[i-1][1]+(a[i]=='J');
		dis[i][2]=dis[i-1][2]+(a[i]=='O');
		dis[i][3]=dis[i-1][3]+(a[i]=='I');
	}ans=m;//以上是前缀和优化。
	for(int i=1;i<=m;i++){
		int x=ksm(4,n-1),y=i-1,q=i-1;
		sum=0;int Q=1;
		while(x!=0){
			y=y+x;
			if(y>m){
				sum=sum+x-(dis[m][Q]-dis[q][Q]);
				sum=sum-(dis[(y-m)][Q]);Q++;//加上贡献。
			}else{
				sum=sum+x-(dis[y][Q]-dis[q][Q]);Q++;//同理
			}
			while(Q>=4) x/=4,Q-=3;q=y;
			while(q>m) q-=m;while(y>m) y-=m;//防止超界。
		}
		ans=min(ans,sum);
	}wh(ans);
	return 0;
}
```

---

## 作者：Lame_Joke (赞：0)

- ### 大体思路

  首先明确一点，无论 $K$ 等于几，最后得出的 $S_k$ 都只有三种可能，并且只有最后一位是可变的，所以我们考虑的时候不需要考虑最后一位。

  接下来考虑算法，贪心是肯定不可能的，DP……不会，那就暴力！考虑求每一位开始读的答案，那么就有一种很暴力的做法是枚举整个环求答案，但是很明显，这是文字数量的平方的，而文字数量最高可达 $4^{10}$ 。那难道就要换算法了么，当然不换，毕竟去想别的也想不出来。

  那就考虑怎么优化这个暴力。我们发现像上面那样求答案会重复求很多部分，我们定义分界为一串相同字母与另一串的分界，易求，这里就不过多解释。举个例子，我们现在求的是从第 $x$ 位开始读的答案，但是改变的也不过是每一个分界的开头和结尾罢了，所以可以只求从第一位开始读的答案，后面可以继承前面的答案，再根据每一个分界点的开头和结尾来进行修改。

- ### 具体实现

 ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int k,len,cnt=0,fj[55],ans,pw;
  char s[1100005],zh[3];
  int nw=0;
  inline void dfs(int k1)
  {
  	if(k1==0) return;
  	pw=pow(4,k1-1);
  	fj[nw+1]=fj[nw]+pw,fj[nw+2]=fj[nw]+2*pw,fj[nw+3]=fj[nw]+3*pw;
  	nw+=3;
  	for(int i=fj[nw-3];i<fj[nw];i++)
  	{
  		if(i<fj[nw-2])
  		{
  			if(s[i]!='J') cnt++;
  		}
  		else if(i<fj[nw-1])
  		{
  			if(s[i]!='O') cnt++;
  		}
  		else if(i<fj[nw]) 
  		{
  			if(s[i]!='I') cnt++;
  		}
  	}
  	dfs(k1-1);
  }
  int main()
  {
  	scanf("%d",&k);
  	scanf("%s",&s);
  	len=pow(4,k);
  	zh[1]='J';
  	zh[2]='O';
  	zh[0]='I';
  	dfs(k);
  	ans=cnt;
  	for(int i=1;i<len;i++)
  	{
  		for(int j=1;j<=nw;j++)
  		{
  			if(s[fj[j-1]]==zh[j%3]&&s[fj[j]]!=zh[j%3]) cnt++;
  			else if(s[fj[j-1]]!=zh[j%3]&&s[fj[j]]==zh[j%3]) cnt--;
  		}
  		for(int j=0;j<=nw;j++) fj[j]++,fj[j]%=len;
  		ans=min(ans,cnt);
  	}
  	printf("%d\n",ans);
  }
  ```

---

