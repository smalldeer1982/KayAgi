# Even Parity

## 题目描述

给你一个 $n \times n$ 的 $01$ 矩阵（每个元素非 $0$ 即 $1$），你的任务是把尽量少的 $0$ 变成 $1$，使得原矩阵便为偶数矩阵（矩阵中每个元素的上、下、左、右的元素（如果存在的话）之和均为偶数）。

## 样例 #1

### 输入

```
3
3
0 0 0
0 0 0
0 0 0
3
0 0 0
1 0 0
0 0 0
3
1 1 1
1 1 1
0 0 0```

### 输出

```
Case 1: 0
Case 2: 3
Case 3: -1```

# 题解

## 作者：弹星者 (赞：3)

思路：**枚举第一行的所有情况**（因为只看上下左右，所以第一行确定后，就可以确定剩余行的情况了QwQ）     
这里我们**采用x状压一下**，然后从小到达枚举x（即枚举把第一行的哪些0变成1），把修改过第一行的原数组存到b数组中（ps：要判断**有没有把1改成0**，改了则不行，跳过）。        
然后根据第一行确定要变化其他行的哪些数字，如果**存在需要把1改成0的情况，则此方案不行。**        
最后取每种情况的最小值就好啦~ 附上本蒟蒻的代码QWQ
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,ans;
int a[20][20],b[20][20];//b存每种情况修改后的数组
int dx[3]={0,0,-1};
int dy[3]={1,-1,0};//上左右三个方向
int check(int m){//当第一行的情况为m时
	int num=0;//需要修改的次数
	for(int i=n;i>=1;i--){
		b[1][i]=m&1;
		m=m>>1;
		if(a[1][i]==0&&b[1][i]==1)
			num++;
		if(a[1][i]==1&&b[1][i]==0)//如果把1变为0了
			return 0x7fffffff;//此方案不行
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=n;j++){
			int sum=0;
			for(int k=0;k<3;k++){
				int xx=dx[k]+i;
				int yy=dy[k]+j;
				if(xx>0&&xx<=n&&yy>0&&yy<=n)
					sum+=b[xx][yy];			
			}
			if(sum%2==0&&b[i+1][j]==1) return 0x7fffffff;//三个方向
            和为偶数，下方数为0，不行
			if(sum%2==1&&b[i+1][j]==0) b[i+1][j]=1,num++;//0改1
		}
	}
	return num;
}
int main(){
	scanf("%d",&t);
	for(int cas=1;cas<=t;cas++){
		ans=0x7fffffff;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%d",&a[i][j]);
		for(int i=1;i<=n;i++)		
			x+=x<<2+a[1][i];
		for(int i=x;i<(1<<n);i++){//枚举第一行
			for(int xx=1;xx<=n;xx++)
				for(int yy=1;yy<=n;yy++)
					b[xx][yy]=a[xx][yy];
			ans=min(ans,check(i));
		}	
		if(ans==0x7fffffff) printf("Case %d: -1\n",cas);
		else printf("Case %d: %d\n",cas,ans);
	}
	return 0;
}
```


---

## 作者：Tethys (赞：2)

[题面](https://www.luogu.com.cn/problem/UVA11464)

### 题意：

给你一个$01$矩阵，求最小的操作次数（将$0$变为$1$）使得矩阵满足条件（节点的上下左右四个方向总和为偶数）

### 思路：
每个合法的矩阵都可以通过第一行推出来，

所以我们可以通过枚举矩阵的第一行，然后判断是否能成为合法的矩阵，

但是必须要满足条件（不能讲原矩阵中的$1$改为$0$）

因为$n$很小，所以这种枚举是能过的

### 实现：
我们考虑要确定当前$(i,j)$这个点的状态了，

我们要保证$(i-1,j)$这个点满足条件，

所以tmp[i][j]=(tmp[i-2][j]+tmp[i-1][j-1]+tmp[i-1][j+1])&1

然后判断一下是否合法就好了

### 代码：
```cpp
#include<bits/stdc++.h>

namespace Tethys{
	inline long long read(){
		long long s = 0, f = 1; char ch;
		while(!isdigit(ch = getchar())) (ch == '-') && (f = -f);
		for(s = ch ^ 48; isdigit(ch = getchar()); s = (s << 1) + (s << 3) + (ch ^ 48));
		return (s *= f);
	}
}

using namespace std;
using namespace Tethys;
const int N = 15 + 5, INF = 666;

int T, n, ans;
int a[N][N], tmp[N][N];

int dfs(int now){
	int res = 0;
	for(int i = 0; i <= n; i ++){
		for(int j = 0; j <= n + 1; j ++) tmp[i][j] = 0;
	}
	for(int i = 1; i <= n; i ++){
		if(now & (1 << (i - 1))) tmp[1][i] = 1;
		if(!tmp[1][i] && a[1][i]) return INF;
		if(tmp[1][i] && !a[1][i]) res ++;
	}
	for(int i = 2; i <= n; i ++){
		for(int j = 1; j <= n; j ++){
			tmp[i][j] = (tmp[i - 2][j] + tmp[i - 1][j - 1] + tmp[i - 1][j + 1]) & 1;
			if(!tmp[i][j] && a[i][j]) return INF;
			if(tmp[i][j] && !a[i][j]) res ++;
		}
	}
	return res;
}
 
signed main(){

	T = read();
	for(int t = 1; t <= T; t ++){
		n = read(); ans = INF;
		for(int i = 1; i <= n; i ++){
			for(int j = 1; j <= n; j ++) a[i][j] = read();
		}
		for(int i = 0; i < (1 << n); i ++) ans = min(ans, dfs(i));
		
		printf("Case %d: %d\n", t, ans == INF ? -1 : ans);
	}
	
	fclose(stdin); fclose(stdout);
	return 0;
}
```
完美撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：cyr2003 (赞：2)

蒟蒻的我又来发一篇 普及/提高- 的题解（好像是第一次qwq）

### 切入正题：

首先我们来考虑这个只有0和1的矩阵，因为每个位置的上、下、左、右（假设有的话）之和必须为偶数，所以我们可以根据上一行来逐次推出后面的若干行

### 也就是说：

我们可以枚举第一行的所有情况（用二进制来处理（因为是01矩阵）），然后根据不同情况来递推，最后打出最小的ans

### 看代码：

```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define INF 10000000;
using namespace std;
int n,t,ans,pd; //pd用来判断答案是否更新
int a[20][20],b[20][20]; //b数组存贮修改后的矩阵
int doit(int p) //操作过程
{
    int c=0,x,k;
    memset(b,0,sizeof(b));
    for(int i=1;i<=n;i++) //枚举第一行
	{
		x=p&1; //等价于x=p%2;
		p/=2;
		b[1][i]=x;
		if (b[1][i]!=a[1][i]) if(x==1) c++; else return 0; //如果把0改成1了就不行，返回0
	}
	for(int i=2;i<=n;i++) //第一行已知，故从第二行开始递推
	 for(int j=1;j<=n;j++)
	  {
	   k=b[i-1][j-1]+b[i-1][j+1]+b[i-2][j]; //k为b[i-1][j]的上、左、右位置之和
	   k%2==1?b[i][j]=1:b[i][j]=0; //若k不是偶数，则b[i][j]肯定要改
	   if (b[i][j]!=a[i][j]) if(b[i][j]==1) c++; else return 0; //计数器更新
	  }
	ans=min(ans,c); //更新答案
	return 0;
}
int main()
{
    int ws;
    cin>>t;
    for (int i=1;i<=t;++i)
    {
        ans=pd=INF;
        cin>>n;
        ws=(1<<n); //1<<n = 2^n
        for(int i=1;i<=n;++i)
		 for(int j=1;j<=n;++j)
		  cin>>a[i][j]; //读入
		for (int i=1;i<=ws;++i)
		 doit(i); //枚举，递推
		if (ans==pd) ans=-1; //判断答案
		cout<<"Case "<<i<<": "<<ans<<endl; //输出
    }
    return 0;
}

```
### 完美结束（0^w^0）

---

## 作者：hyjdouSHEN (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/UVA11464)

## 题目分析

也许最容易想到的方法就是**暴力**！但是现实是残酷的，暴力的做法最多需要枚举 $2^{255}$，大约就是 $5 \times 10^{67}$ 种情况，实在难以接受。

注意到 $n$ 只有 $15$，第一行只有不超过 $2^{15}=32768$ 种可能，所以第一行的情况。接下来，根据第一行的情况完全可以推出第二行的情况，第二行又可以推出第三行，以此类推，总时间复杂度即可将为 $ \Theta (2^{n}\times n^{2})$。

代码如下。

## 代码部分

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=20;
const int INF=1000000000;
int n,a[maxn][maxn],b[maxn][maxn];
int check(int s){
	memset(b,0,sizeof(b));
	for(int c=0;c<n;c++){
		if(s&(1<<c)) b[0][c]=1;
		else if(a[0][c]==1) return INF;  //1不能变成0 
	}
	for(int i=1;i<n;i++){
		for(int j=0;j<n;j++){
			int sum=0;     //元素b[i-1][j]的上左右三个元素的和 
			if(i>1) sum+=b[i-2][j];
			if(j>0) sum+=b[i-1][j-1];
			if(j<n-1) sum+=b[i-1][j+1];
			b[i][j]=sum%2;
			if(a[i][j]==1&&b[i][j]==0) return INF; //1不能变成0 
		}
	}
	int cnt=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(a[i][j]!=b[i][j]) cnt++;
		}
	}
	return cnt;
}
int main()
{
	int t;
	scanf("%d",&t);
	for(int gg=1;gg<=t;gg++){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				scanf("%d",&a[i][j]);
			}
		}
		int ans=INF;
		for(int k=0;k<(1<<n);k++){
			ans=min(ans,check(k));
		}
		if(ans==INF) ans=-1;
		printf("Case %d: %d\n",gg,ans);
	}
	return 0;
}
```

希望这篇题解对你有帮助~

[AC记录](https://www.luogu.com.cn/record/120885440)

---

## 作者：CRTL_xzh2009 (赞：1)

看一下样例。


```
3
0 0 0
1 0 0
0 0 0
```

对于第一行第一个的 $0$，要满足条件，第一行第二个的 $0$ 改为 $1$。当然，还有其他的解法，但这个是改动最少的，这里不一一枚举了。同理：

第一行变为 `0 1 0`。

第二行变为 `1 0 1`。

第三行变为 `0 1 0`。

变了 $3$ 个，故为 $3$。

只要第一行确定，那么接下来就可以顺水推舟地写出来。

**那第一行如何枚举呢？**

设置数组 `A[i][j]` 表示原矩阵。对于每一行，**从右往左** 找第一个 $0$，找到改为 $1$，它后面的改为 $0$。

例如对于 `0 0 0`，改为 `0 0 1`，再改为 `0 1 0`，再改为 `0 1 1`，以此类推。


```cpp
for(i=n;c[i]==1;i--)c[i]=0;
c[i]=1;
```

以上代码可解决此问题。

再定义 `B[i][j]` 存 `c[j]`。

```cpp
int sum=0;
if(i>1) sum+=B[i-1][j];
if(j>1) sum+=B[i][j-1];
if(j<n) sum+=B[i][j+1];
B[i+1][j]=sum%2;
```

再对比一下 $A$ 与 $B$。若 $A$ 为 $0$ 而 $B$ 为 $1$，$ans$ 加 $1$。若 $A$ 为 $1$ 而 $B$ 为 $0$，则不能改。

好了，代码奉上：

```cpp
#include<bits/stdc++.h>//
using namespace std;
const int oo=0x7f7f7f7f;
int t,n,A[20][20],B[20][20],C[20];
void init()
{
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	    for(j=1;j<=n;j++)
	        scanf("%d",&A[i][j]);
}
int check()//检查第一行状态为C[]时能否满足条件
{
    int i,j,cnt;
    memset(B,0,sizeof(B));
	for(j=1;j<=n;j++)//第一行
	    if(C[j]==1)
            B[1][j]=1;
		else
            if(A[1][j]==1) return oo; //1不能变成0
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        {
		    int sum=0;
		    if(i>1) sum+=B[i-1][j];
		    if(j>1) sum+=B[i][j-1];
		    if(j<n) sum+=B[i][j+1];
		    B[i+1][j]=sum%2;
			if(A[i+1][j]==1 && B[i+1][j]==0) return oo; //1不能变成0
        }
    cnt=0;
    for(i=1;i<=n;i++)//统计将多少个0变成1
	    for(j=1;j<=n;j++)
            if(A[i][j]!=B[i][j]) cnt++;
	return cnt;
}
void work()
{ 
    int i,ans=oo;
	while(C[0]==0)
    {
	    for(i=n;C[i]==1;i--)C[i]=0;//从右向左找到第一个0,将它后面所有的1变为0
		C[i]=1;
        ans=min(ans,check());
	}
    if(ans==oo) ans=-1;
	printf("%d\n",ans);
}
int main()
{
	//freopen("matrix.in","r",stdin);
	//freopen("matrix.out","w",stdout);
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		memset(A,0,sizeof(A));
		memset(B,0,sizeof(B));
		memset(C,0,sizeof(C));
		init();
		printf("Case %d: ",i);
	   work();
	}
	return 0;
}
```


---

## 作者：残阳如血 (赞：1)

# 思路分析
## 暴力枚举？
我们可以枚举每个数字变或不变，最后判断整个矩阵是否满足条件。但是，这样做最多需要枚举 $2^{255}≈5\times10^{67}$ 中情况，是一定会超时的。
## 大眼观察
注意到 $n\le15$，第一行只有不超过 $2^{15}=32768$ 种可能，所以第一行的情况是可以枚举的。接下来，根据第一行可以计算出第二行，根据第二行又能计算出第三行，以此类推，总时间复杂度即可降为 $\mathcal O(2^n\times n^2)$。
# 程序实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20;
const int INF = INT_MAX;
int T, n, A[MAXN][MAXN], B[MAXN][MAXN];
int check(int s) { // 检查+扩展
	memset(B, 0, sizeof(B));
	for (int c = 0; c < n; c++) {
		if (s & (1 << c)) B[0][c] = 1;
		else if (A[0][c] == 1) return INF;
	}
	for (int r = 1; r < n; r++)
		for (int c = 0; c < n; c++) {
			int sum = 0;
			if (r > 1) sum += B[r - 2][c];
			if (c > 0) sum += B[r - 1][c - 1];
			if (c < n - 1) sum += B[r - 1][c + 1];
			B[r][c] = sum % 2;
			if (A[r][c] == 1 && B[r][c] == 0) return INF;
		}
	int cnt = 0;
	for (int r = 0; r < n; r++)
		for (int c = 0; c < n; c++)
			if (A[r][c] != B[r][c])
				cnt++;
	return cnt;
}
int main() {
	cin >> T;
	for (int cnt = 1; cnt <= T; cnt++) {
		cin >> n;
		for (int r = 0; r < n; r++)
			for (int c = 0; c < n; c++)
				cin >> A[r][c];
		int ans = INF;
		for (int s = 0; s < (1 << n); s++)
			ans = min(ans, check(s));
		if (ans == INF) ans = -1;
		printf("Case %d: %d\n", cnt, ans);
	}
	return 0;
}
```

---

## 作者：Toorean (赞：1)

# 题目描述

给出一个仅包含 $\{0,1\}$ 的 $n\times n$ 矩阵，

使得 $arr$ 中任意一个位置 $(x,y)$ 满足 $(arr[x-1][y]+arr[x][y-1]+arr[x][y+1]+arr[x+1][y])\mod2 == 0$ 这一条件。

且仅可改变矩阵任意一位置的元素为 $1$，

求最小改变次数。

(无解则输出 $-1$)

---

# 思路
## 暴力解法

由于矩阵 $arr$ 仅包含 $\{0,1\}$ 个元素，因此可把矩阵看为一个**二进制数**构成的矩阵。于是便可想到枚举每一种可能的答案。因为 $n\times n$ 为矩阵大小，因此这个二进制数的长度为 $n^2$，因此有 $2^{n·n}$ 种可能。可是这种方法极度限制 $n$ 的大小，当 $n\geq6$ 时就已经不可以满足题目所给的条件。

## 优化+AC解法
由于不可以直接暴力枚举 $n^2$ 可能性的矩阵，我们不妨推理一下矩阵的组成。矩阵第一行每列元素的值是无法通过已有的元素来确定的，因此这也难免要枚举第一行元素的值。因此可先写出枚举代码:

```cpp
int changed_arr[MAXN][MAXN]; // 令本数组为改变后的 arr 矩阵。
for(int i = 0; i < (1 << n); i++) { // (1 << n) == (2 ^ n) 。
    memset (changed_arr, 0, sizeof (changed_arr));
    int s = i;
    for (int j = 1; j <= n; j++){
        if (s & 1) {		// 等同于 s % 2 == 1 （优化时间复杂度）。
            new_arr[1][j] = 1; 
        } else if (arr[1][j]) { // 否则的话 当前这一位为 0， 由于前面已经初始化过改变后的数组了，因此无需考虑 !arr[1][j] 且 !(s & 1) 的情况了。
            break ;     
            /* 
              由于题目只允许将元素为 0 改为元素为 1，而列举到的
              本二进制数却与原矩阵中 1 改变为了0，因此不符合题  
              意，便舍去这一可能。
            */
        }
    }
    
    /*
    这一枚举方法是为逆向枚举，从高位向低位依次取出后放入
    新矩阵的低到高位，由于不论是从低到高还是从高到低，都
    会枚举一遍，因此无需考虑先后顺序。
    */
}

```

确定好了第一行，我们也就可以进行推理解题了。

首先，我们可以拿题目的样例来作为参考。


0 0 0

1 0 0

0 0 0

那么第一行也就有这么几种情况:

* 0 0 0
 
 既 $changed\_arr[1][] = {0, 0, 0, 0}$。
 如果要让 $changed\_arr[2][1]$ 表示的数满足题意的话，(因为这个数只能影响它的四周，而我们也仅仅确定了它的上方，因此我们只要考虑它的上方 $changed\_arr[1][1]$)
 
 那么 $changed\_arr[1][2]+changed\_arr[2][1]$ 的和必须是偶数。
 
 因为 $changed\_arr[1][2] = 0$，
 
 所以 $changed\_arr[2][1] = 0$，
 
 但是 $arr[2][1] = 1$,
 
 所以本解法不符合题意，舍去。


* 0 1 0
 
 既 $changed\_arr[1][] = {0, 0, 1, 0}$。
 
 如果要让 $changed\_arr[2][1]$ 表示的数满足题意的话，
 
 那么 $changed\_arr[1][2]+changed\_arr[2][1]$ 的和必须是偶数，
 
 因为 $changed\_arr[1][2] = 1$，
 
 所以 $changed\_arr[2][1] = 1$，
 
 满足题意，因此 $changed\_arr[2][1] = 1$。

 于是便开始确定 $changed\_arr[2][2]$ 的元素，
 
 确定方法与上述一致，我们无需考虑上一列的元素，只需要考虑上一行的元素。
 
 因为我们每次确保的是上方元素合理，而每次的确定元素操作也就是确保上方合理的过程，
 
 这样也就正好保证了答案的正确性。

* $……$


最后，我们就得到了一个符合题意的矩阵，之后可再遍历一遍修改的矩阵与原矩阵相比较，获得答案。将不同方案的答案比较得出最小值，即可 AC 本题。

---
# AC Code

```cpp
#include <cstdio>
#include <cstring>

#define min(x,y) (x < y ? x : y)	// 求两数中较小值。
#define MAXN 30
#define INF 0x3f3f3f3f	

int n, ans = INF;
int arr[MAXN][MAXN], new_arr[MAXN][MAXN];

int getAns (int s) {
    memset (new_arr, 0, sizeof (new_arr));
    for (int i = 1; i <= n; i++) {
        if (s & 1) {	// 位运算较快 等价于 s % 2 == 1 。
            new_arr[1][i] = 1;
        } else if (arr[1][i] == 1) {
            return INF;  // 判断修改是否合法。
        }
        s >>= 1;  // 等价于 s | 2。
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int sum = 0;
            if (i > 2) { sum += new_arr[i - 2][j]; } 
            if (i > 1 && j > 1) { sum += new_arr[i - 1][j - 1]; }
            if (i > 1 && j < n) { sum += new_arr[i - 1][j + 1]; }
            // 判断是否在矩阵内。
            if (!(sum & 1)) {
                if (arr[i][j]) {
                    return INF;
                } // 判断修改是否合法。
            } else {
                new_arr[i][j] = 1;
            }
        }
    }

    int counts = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (new_arr[i][j] != arr[i][j]) {
                ++ counts;	
            }
        }
    } // 获取修改元素个数。

    return counts;
}

int main (void) {

    int t;
    scanf ("%d", &t);
    for (int l = 1; l <= t; l++) {
        ans = INF;
        memset (arr, 0, sizeof (arr));

        scanf ("%d", &n);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                scanf ("%d", &arr[i][j]);
            }
        }

        for (int i = 0; i < (1 << n); i++) { // (1 << n) 等价于 2^n。
            ans = min (ans, getAns (i));
        }

        if (ans == INF) { ans = -1; }	// 当ans等于INF时，答案未改变，所以无解。
        printf ("Case %d: %d\n", l, ans);
    }
    

    return 0;
}

```

---
# 时间复杂度
$ O(T * 2^n * n^2) $

勉强能过。

---

## 作者：shzaiz (赞：1)

#### [Even Parity ](https://www.luogu.com.cn/problem/UVA11464)

##### 分析

如果固定了第一行，那么一定只有一种修改方式。

如果$C(A_{i,j})=$odd,那么必须修改$A_{i+1,j}$.才可以保证解。



我们的方案是通过二进制枚举子集第一行s，交给check()验证。如果成功返回不同的ans，不成功就返回INF.

注意$0\rightarrow1$是可以的，$1\rightarrow0$ 不行。
$$

$$


##### 代码实现

```cpp
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;
const int MAXN  = 20;
const int INF = 1110000000;
int n,A[MAXN][MAXN],B[MAXN][MAXN];
//A--原矩阵 B--修改矩阵
int check(int s){
	memset(B,0,sizeof B);
	for(int i=0;i<n;i++){ //检查第一行
		int comp = s&(1<<i); //取出来相应数字
		if(comp) B[0][i] = 1;
		else if(A[0][i]==1){ //检查是不是可以变化。
			return INF;
		}
			
		
	}
	for(int r=1;r<n;r++){
		for(int c=0;c<n;c++){
			int sum = 0;
            
            /*
             用B[r-1][c+1]+B[r-2][c]+B[r-1][c-1]...
             
             B[r-2][c-1]   B[r-2][c]   B[r-2][c+1]
             B[r-1][c-1]   B[r-1][c]   B[r-1][c+1]
             B[ r ][c-1]   B[ r ][c]   B[ r ][c+1]
            */
			if(r>1) sum+= B[r-2][c];
			if(c>0) sum+= B[r-1][c-1];
			if(c<n-1) sum+= B[r-1][c+1];
			//...推断B[r][c]
            B[r][c] = sum%2;
            //如果不可取：
			if(A[r][c] == 1 && B[r][c]==0 ) {
				return INF;
				
			}
			
		}
	}
	int cnt = 0;
	for(int r=0;r<n;r++){
		for(int c=0;c<n;c++){
			if(A[r][c]!=B[r][c]) cnt++;
		}
	}
	return cnt;
}
int main(){
	int T;
	cin>>T;
	for(int ka = 1;ka<=T;ka++){
		cin>>n;
		for(int r=0;r<n;r++){
			for(int c=0;c<n;c++){
				cin>>A[r][c];
			}
		} 
		int ans = INF;
		for(int s = 0;s<(1<<n);s++){
			ans = min(ans,check(s));
			
		} 
		if(ans==INF) ans = -1 ;
		cout<<"Case "<<ka<<": "<<ans<<"\n";
	}
	return 0;
}
```



##### 技巧分析

###### 使用二进制枚举子集

```cpp
for(int s = 0;s<(1<<n);s++){
    ...
}
```

在后面加入一个合法字符串。

1. 取第i位的二进制值：

   如果压缩的字符串是s，取第c位：

   ```cpp
   s&(1<<c);
   ```

###### 使用比较不错的英文名字

row = 行 ， column=列

###### 对于越界情况的处理

使用分步相加。


---

## 作者：Ferdina_zcjb (赞：0)

这道 dfs 挺有趣的。

# 暴力

暴力的话最坏情况枚举 $2^{255}$ 的情况，放眼看去是肯定不行的，考虑如何优化。

# 优化 dfs

首先我们手模一下，在暂时确定了一个矩阵的情况下，需要去改变它。首先，是 $1$ 的位置是绝对不能改变的（好像说了句废话）。

重点来了！当我们手模了矩阵第一行时，自上而下、自左向右的可以递推出所有各自的状态（保证题目所要求的是最小个数的情况下）。读者可以自行去尝试。

所以，枚举第一行的所有情况，在进行筛查，对所有合法值打擂台即可得出正确答案。

二进制枚举第一行：

```cpp
for(int i = 0;i < len;++i){
	if(num&(1<<i))g2[0][i] = 1;
	else if(g[0][i] == 1)return INF;
}
```

筛查（以 $1$ 的位置是绝对不能改变为筛查标准）：

```cpp
for(int i = 1;i < len;++i){
	for(int j = 0;j < len;++j){
		int sum = 0;
		if(i > 1)sum += g2[i-2][j];
		if(j > 0)sum += g2[i-1][j-1];
		if(j < len-1)sum += g2[i-1][j+1];
		g2[i][j] = sum%2;
		if(g[i][j] == 1 && g2[i][j] == 0)return INF;
	}
}
```


最后是整体代码，记得多测清空：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 0x7fffffff;
int T,g[20][20],g2[20][20];
int check(int len,int num){
	for(int i = 0;i < len;++i){
		for(int j = 0;j < len;++j){
			g2[i][j] = 0;
		}
	}
	for(int i = 0;i < len;++i){//第一行枚举并筛查不合法情况。
		if(num&(1<<i))g2[0][i] = 1;
		else if(g[0][i] == 1)return INF;
	}
	int ret = 0;
	for(int i = 1;i < len;++i){//筛查。
		for(int j = 0;j < len;++j){
			int sum = 0;
			if(i > 1)sum += g2[i-2][j];
			if(j > 0)sum += g2[i-1][j-1];
			if(j < len-1)sum += g2[i-1][j+1];
			g2[i][j] = sum%2;//确定g2[i][j]的值。
			if(g[i][j] == 1 && g2[i][j] == 0)return INF;
		}
	}
	for(int i = 0;i < len;++i){
		for(int j = 0;j < len;++j){
			if(g[i][j] != g2[i][j]){
				ret ++;
			}
		}
	}
	return ret;
}
signed main() {
	scanf("%lld",&T);
	int k = 0;
	while(T--){
		k++;
		int n;
		scanf("%lld",&n);
		for(int i = 0;i < n;++i){
			for(int j = 0;j < n;++j){
				cin >> g[i][j];
			}
		}
		int ans = INF;//初始化ans。
		for(int i = 0;i < (1 << n);++i){
			ans = min(check(n,i),ans);
		}
		printf("Case %lld: ",k);
		if(ans == INF)cout << -1 << endl;//判断无解。
		else cout << ans << endl;
	}
}	 
```



---

## 作者：Lyccrius (赞：0)

注意到 $n$ 只有 $15$，第一行只有不超过 $2^{15} = 32768$ 种可能，所以第一行的情况时可以枚举的。接下来，根据第一行可以完全计算出第二行，根据第三行又能计算出第三行，以此类推，总时间复杂度为 $\mathcal{O} (2^n \times n^2)$。

```
#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 15 + 10;
const int inf = 0x3f3f3f3f;

int T;

int n;
int originGrid[maxn][maxn];
int grid[maxn][maxn];

int check(int line) {
    std::memset(grid, 0, sizeof(grid));
    for (int i = 1; i <= n; i++) {
        if (line >> (i - 1) & 1) grid[1][i] = 1;
        else if (originGrid[1][i]) return inf;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int sum = 0;
            if (i > 2) sum += grid[i - 2][j];
            if (j > 1) sum += grid[i - 1][j - 1];
            if (j < n) sum += grid[i - 1][j + 1];
            grid[i][j] = sum % 2;
            if (originGrid[i][j] && !grid[i][j]) return inf;
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (originGrid[i][j] != grid[i][j]) cnt++;
    return cnt;
}

int main() {
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) scanf("%d", &originGrid[i][j]);
        int maxOpt = 1 << n;
        int ans = inf;
        for (int opt = 0; opt < maxOpt; opt++) ans = std::min(ans, check(opt));
        if (ans == inf) ans = -1;
        printf("Case %d: %d\n", kase, ans);
    }
    return 0;
}
```

---

## 作者：翼德天尊 (赞：0)

一道很好的思维题。

首先考虑暴力枚举。

由于对于矩阵上的每一个点都有 $0$ 和 $1$ 两种可能，如果递归暴力枚举每一个点，复杂度最高则会达到恐怖的 $O(2^{15\times15})=O(2^{225})$，显然超时。

那么怎么降复杂度呢？

很容易想到的就是贪心，考虑是否存在一种特定的模型，使得我们可以快速求解。但是关于这个模型想了半天我也没有想到。

那么基本就只能暴力了。

这道题很难想到的一点就是，如果第一行确定下来，为了使这个矩阵尽可能地有解，后面的点的值也都能确定下来。

比如第一行是 `0 1 0`，那么为了使第一行第一个的 $0$ 合法，第二行第一个必定是 $1$，为了使第一行第二个合法，第二行第二个必定是 $0$，以此类推。


由此我们就可以确定出整个矩阵。在确定矩阵的过程中和输入矩阵比较即可，如果发现矛盾则返回继续枚举。最后将所有合法方案的修改数取最小值即为最终答案。如果没有合法方案最后输出 `-1` 即可。

单个矩阵的复杂度为 $O(2^nn^2)$，稳过。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 20
int t,n,anss;
bool ma[N][N],ans[N][N];
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
bool query(int x,int y){
	return (ans[x-1][y]+ans[x][y+1]+ans[x][y-1])&1;
}
void dfs(int now,int sum){
	if (now==n+1){
		for (int i=2;i<=n;i++){
			for (int j=1;j<=n;j++){
				bool jo=query(i-1,j);
				if (jo) sum+=jo-ma[i][j],ans[i][j]=1;
				else{
					if (ma[i][j]==1) return;
					ans[i][j]=0;
				}
			} 
		}
		anss=min(anss,sum);
		return;
	}
	if (ma[1][now]==1) ans[1][now]=1,dfs(now+1,sum);
	else{
		ans[1][now]=0,dfs(now+1,sum);
		ans[1][now]=1,dfs(now+1,sum+1);
	}
	ans[1][now]=0;
} 
int main(){
	t=read();
	for (int cas=1;cas<=t;cas++){
		printf("Case %d: ",cas);
		memset(ans,0,sizeof(ans));
		anss=999999;//记得初始化数组
		n=read();
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				ma[i][j]=read();
		dfs(1,0);
		if (anss==999999) puts("-1");
		else printf("%d\n",anss); 
	}
	return 0;
}
```


---

## 作者：swl3992 (赞：0)

首先我们可以想到暴力枚举每个数字变还是不变，可以显然时间复杂度太高。

于是，我们可以想到可以枚举第一行，根据第一行可以计算出第二行，根据第二行可以计算出第三行……

可以使用二进制枚举。

那么如何计算呢？

很简单。我们可以 计算当前元素的**上面的**元素的上、左、右（下面正在计算），如果为偶数，那么这一个为 0 , 否则为 1 .

注意：0 可以变成 1 , 1 不能变成 0 .

示例代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int num[20][20];	//原来的
int test[20][20];	//当前的
int n;
int solve(int S)
{
    for(int i=0;i<n;i++)
    {
        if(S&(1<<i))	//如果为 1
        {
            test[0][i]=1;
        }
        else if(num[0][i]==1)	//1 不能变 0
        {
            return 2147483647;
        }
    }
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            int sum=0;	//计算 test[i-1][j] 的上、左、右的和
            if(i>1)
            {
                sum+=test[i-1-1][j];
            }
            if(j>0)
            {
                sum+=test[i-1][j-1];
            }
            if(j<n-1)
            {
                sum+=test[i-1][j+1];
            }
            test[i][j]=sum%2;	//这一个元素应为什么
            if(test[i][j]==0&&num[i][j]==1)	//1 不能变 0
            {
                return 2147483647;
            }
        }
    }
    int temp=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(num[i][j]!=test[i][j])
            {
                temp++;
            }
        }
    }
    return temp;
}
int main()
{
    int T;
    cin>>T;
    int Case=0;
    while(T--)
    {
        cin>>n;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                cin>>num[i][j];
            }
        }
        int ans=2147483647;
        for(int S=0;S<(1<<n);S++)	//枚举第一行
        {
            memset(test,0,sizeof(test));
            ans=min(ans,solve(S));
        }
        if(ans==2147483647)
        {
            ans=-1;
        }
        cout<<"Case "<<++Case<<": "<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：lowAltitudeFlyer (赞：0)

## Description
给你一个$n$行$n$列的01矩阵（每个元素非$0$即$1$），你的任务是把尽量少的$0$变成$1$，使得每个元素的上、下、左、右的元素（如果存在的话）之和均为**偶数**。

注意，题目翻译中把**偶数**翻译成了**整数**。（至少在作者写这篇题解的时候仍然存在这个错误）
## Solution
这道题类似于《算法竞赛进阶指南》0x02 递推与递归中的例题[费解的开关](http://noi-test.zzstep.com/contest/0x00%E3%80%8C%E5%9F%BA%E6%9C%AC%E7%AE%97%E6%B3%95%E3%80%8D%E4%BE%8B%E9%A2%98/0201%20%E8%B4%B9%E8%A7%A3%E7%9A%84%E5%BC%80%E5%85%B3)。

深入挖掘题目性质后，我们发现，若固定了第一行，则满足题意的修改方案至多只有一种。  
分析：当第$i$行第$j$列的数上、下、左、右的元素之和为奇数时，必须修改第$i+1$行第$j$列的数（如果第$i+1$行第$j$列的数不可以修改，则当前这种第一行的修改方案不可行），才能使其满足条件。从上到下按行使用归纳法即可得到之前所说的结论。

所以我们只需要递归枚举第一行的修改方案，再考虑第$2$到$n$行如何修改即可。具体实现见代码及注释。
## Tips
- 注意细节和边界情况

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 15 + 5;
int T, n, ans, cnt;
int a[MAXN][MAXN], b[MAXN][MAXN];
void change(int x, int y) {
	a[x][y] ^= 1;
}
int sum(int x, int y) { //求(x,y)的上、下、左、右的元素之和 
	return a[x-1][y] + a[x+1][y] + a[x][y-1] + a[x][y+1]; //如果上、下、左、右中的某个元素不存在，则该位置已被初始化为0，不需要特判 
}
void dfs(int d) {
	if(d == n+1) { //第一行枚举完成，开始检验 
		int tmp = cnt;
		//b数组是一个临时数组，在修改前把a数组原来的状态转存在b数组中，便于回溯 
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				b[i][j] = a[i][j];
			}
		}
		int flag = 0; //flag表示是否可行 
		for(int i = 2; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				if(sum(i-1, j) % 2 == 1) { //和为奇数，需要修改 
					if(a[i][j] == 1) { flag = 1; continue; } //该位置上的数为1，不能修改 
					change(i, j);
					cnt++;
				}
			}
		}
		for(int i = 1; i <= n; i++) { //显然前n-1行的条件都已被满足，只需要检验第n行 
			if(sum(n, i) % 2 == 1) {
				flag = 1;
			}
		}
		if(flag == 0) ans = min(ans, cnt);
		cnt = tmp;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				a[i][j] = b[i][j];
			}
		}
		return;
	}
	dfs(d+1); //不修改 
	if(a[1][d] == 1) return; //该位置上的数为1，不能修改 
	change(1, d);
	cnt++;
	dfs(d+1); //修改 
	change(1, d);
	cnt--;
}
int main() {
	scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		memset(a, 0, sizeof(a)); //多组数据需要清空数组 
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				scanf("%d", &a[i][j]);
			}
		}
		cnt = 0;
		ans = INT_MAX;
		dfs(1);
		if(ans < INT_MAX) {
			printf("Case %d: %d\n", t, ans);
		}
		else {
			printf("Case %d: -1\n", t);
		}
	}
	return 0;
}
```


---

## 作者：小元勋 (赞：0)


- 给出一个$n*n$的矩阵，将尽量少的$0$修改为$1$。使每个数的上下左右的数的和为偶数。$n<=15$

- 显然不能枚举每个数字变或不变，那样复杂度是$2^{255}=5*10^{67}$。注意到，我们可以枚举第一行的操作，进而通过限制条件推出后面的操作，而仅枚举第一行最多有$2^{15}$种情况，是可以承受的。总时间复杂度为$O(2^{n}n^{2})$

- $b$数组代表的是修改后的矩阵

```cpp
#include <bits/stdc++.h>
using namespace std;
#define maxn 65
#define max_sze 65600
#define INF 500

int T,n,a[maxn][maxn],b[maxn][maxn];

inline int read_() {
	int x_=0,f_=1;char c_=getchar();
	while(c_<'0'||c_>'9') {if(c_=='-') f_=-1;c_=getchar();}
	while(c_>='0'&&c_<='9') {x_=(x_<<1)+(x_<<3)+c_-'0';c_=getchar();}
	return x_*f_;
}

inline int work_(int S) {
	memset(b,0,sizeof(b));
	for(int i=1;i<=n;++i) {
		if((S>>(i-1))&1) b[1][i] = 1;
		else if(a[1][i]) return INF;//1 不能变为 0 
	}
	int sum;
	for(int i=2;i<=n;++i) {
		for(int j=1;j<=n;++j) {
			sum = 0;//sum表示a[i-1][j]的上，左，右之和 
			if(i>=3) sum += b[i-2][j];
			if(j>=2) sum += b[i-1][j-1];
			if((j+1)<=n) sum += b[i-1][j+1];
			sum %= 2;
			//如果和取余为1，则a[i-1][j]的下，即b[i][j]必须为1 
			b[i][j] = sum;
			if(!b[i][j]&&a[i][j]) return INF;
			// 1的位置不能修改为 0 
	   }
    }
    sum = 0;
    for(int i=1;i<=n;++i) {
    	for(int j=1;j<=n;++j) {
    		// 0的位置被修改为 1 
    		if(a[i][j]!=b[i][j]) ++sum;
		}
	}
	return sum;
}

void readda_() {
	T = read_();
	int cnt = 0;
	while(T--) {
		n = read_();
		for(int i=1;i<=n;++i) {
			for(int j=1;j<=n;++j) {
				a[i][j] = read_();
			}
		}
		int ans = INF;
		for(int S=0;S<(1<<n);++S) {
			ans = min(ans,work_(S));
		}
		printf("Case %d: %d\n",++cnt,( ans == INF ? -1 : ans) );
	}
}

int main() {
	//freopen("a.txt","r",stdin);
	//freopen("ac.txt","w",stdout);
	readda_();
	return 0;
}
```


---

## 作者：WinterRain208 (赞：0)

UVA11464 Even Parity

#### 题意

给你一个$n * n$的 $01$ 矩阵（就是每个元素只可能为$0$和$1$），你的任务是把尽量少的 $0$ 变成 $1$ ,使得每个元素的上，下，左，右的元素（存在的情况下）之和均为偶数。

#### 做法

刘汝佳书上的枚举思路。

首先我们考虑深搜，每个点枚举一或零，这样因为$n = 15$，所以复杂度是二的$225$次方，绝对不允许的时间复杂度。期望得分$0$.

第二种做法考虑部分枚举，剩下的可以由枚举的部分推出，如下图。

| 1 | 0 | 1 |
| -----------: | -----------: | -----------: |
| * | * | * |
| * | * | * |

不难看出坐标$(2,2)$的 地方只能填$0$，是由$(1,2)$得出的，以此类推。

于是第二行的数字得出后，我们又可以得出第三行的，往下，往下。

#### 题外话

这题的输入真烦人。

还有这题难度不到蓝，黄比较合适。

代码就不放了，再刘汝佳的书上有，题解撰写不易，点个赞再走吧。


---

