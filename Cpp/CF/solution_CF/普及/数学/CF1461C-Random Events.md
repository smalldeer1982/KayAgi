# Random Events

## 题目描述

Ron is a happy owner of a permutation $ a $ of length $ n $ .

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1461C/11faf1b639f9cfdf4aa7dcbd7d3e47925fd41e48.png)Ron's permutation is subjected to $ m $ experiments of the following type: ( $ r_i $ , $ p_i $ ). This means that elements in range $ [1, r_i] $ (in other words, the prefix of length $ r_i $ ) have to be sorted in ascending order with the probability of $ p_i $ . All experiments are performed in the same order in which they are specified in the input data.

As an example, let's take a look at a permutation $ [4, 2, 1, 5, 3] $ and an experiment ( $ 3, 0.6 $ ). After such an experiment with the probability of $ 60\% $ the permutation will assume the form $ [1, 2, 4, 5, 3] $ and with a $ 40\% $ probability it will remain unchanged.

You have to determine the probability of the permutation becoming completely sorted in ascending order after $ m $ experiments.

## 说明/提示

Explanation of the first test case: It can be demonstrated that whether the final permutation is sorted or not depends solely on sorting being performed in the $ (4, 0.6) $ experiment.

## 样例 #1

### 输入

```
4
4 3
4 3 2 1
1 0.3
3 1
4 0.6
5 3
4 2 1 3 5
3 0.8
4 0.6
5 0.3
6 5
1 3 2 4 5 6
4 0.9
5 0.3
2 0.4
6 0.7
3 0.5
4 2
1 2 3 4
2 0.5
4 0.1```

### 输出

```
0.600000
0.720000
0.989500
1.000000```

# 题解

## 作者：Blunt_Feeling (赞：10)

## CF1461C Random Events 题解

这是一道十分有意思的期望与概率问题，十分建议初学者学习。

首先需要明确一点：对于输入的 $a$ 数组，想要使它变为升序，就必须找到一个 $r_i$，满足下标为 $r_i+1\sim n$ 的所有数已经是排好的。换句话说，要想使 $a$ 数组变为升序，就要在 $m$ 个操作中至少找到一个操作，能够只用这一个操作就排好序。而这些一步就能排好序的操作，就是能够起决定性作用的操作。其余的操作都可以忽略，因为它们都已经包含在那些一步就能排好序的操作中了。

接下来就是求总概率了。拿样例来说：

```cpp
5 3
4 2 1 3 5
3 0.8
4 0.6
5 0.3
```
只有第二个和第三个操作是有用的，如果第二个操作成功，总概率就有 $60\%$，如果没有成功，那 $40\%$ 的几率就要去乘后面的 $30\%$ 的几率，最终总概率一共为 $72\%$。

可以推出：

$$f_i=(1-f_{i-1})×p_i$$

### Code
```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
using namespace std;
const int maxn=100050;
int T,n,m,a[maxn],b[maxn];
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		For(i,1,n) cin>>a[i],b[i]=a[i];
		sort(b+1,b+n+1);
		int mark=0;
		Rep(i,n,1) //从后往前拿ai与排好序的bi比对，找到第一个不同的位置
			if(a[i]!=b[i])
			{
				mark=i;
				break;
			}
		double ans=0;
		while(m--)
		{
			int r;
			double p;
			cin>>r>>p;
			if(r>=mark) //如果r是一个有决定性影响的操作
				ans+=(1-ans)*p;
		}
		if(mark==0) //全部匹配上，成功概率为100%
		{
			cout<<1<<endl;
			continue;
		}
		printf("%.8lf\n",ans);
	}
	return 0;
}
```


---

## 作者：IIIIndex (赞：2)

### 题意：

​	先给你一个$[1,n]$的排列，然后再给你$m$次操作，每次操作有两个参数$r_i$和$p_i$，代表着这次操作有$p_i$的概率将**前**$r_i$个元素按顺序排列，求$m$次操作后排列按升序排列的概率。

### 思路：

​	我们考虑如下一个排列：$[4,3,2,1]$，如果**单纯地**对其前$1/2/3$项排序的话是**没有任何意义的**（因为元素"$4$”永远无法到达最后一个位置），所以说我们必须**从后往前找到第一个不在它顺序位置上的元素的位置**（比如$[4,2,1,3,5]$，我们从后往前看，5在第五个，没问题；3在第四个，但第四个位置对应的元素是4，无法匹配；所以说我们的排序位置从**第四个及以后**便开始有意义了）。题目要求是求**按升序排序**的概率，也就是$1-$不按升序排序的概率，而不按升序排律的概率就是对($1-$**有意义的排序的概率**)进行累乘（代表着每次都没有进行排序）。特别的，如果给出的排列本来就有序，就可以直接输出$1.000000$。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int inf=1e9+7;
const int maxn=1e5+100;
int a[maxn];
 
int main(){
    int t;
    cin>>t;
    while(t--){
        memset(a,0,sizeof(a));
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        int last=n+1;
        for(int i=n;i>0;i--){
            if(a[i]==i){last=i;}					//找到“有意义的排列”的最前端
            else break;
        }
        double ans=1;
        for(int i=0;i<m;i++){
            int r;double p;
            cin>>r>>p;
            if(r>=last-1){
                ans*=(1-p);							//累乘
            }
        }
        if(last==1){printf("1.000000\n");}			//特判
        else{printf("%.6lf\n",1-ans);}
    }
```

---

## 作者：违规用户名gAGt8$%z (赞：1)

## 思路
对于输入的 $a$ 数组，想要使它变为升序，就必须找到一个 $x$ 使得    $a_{x+1} ∼ a_{n}$ 是已经排序好的 ， 显而易见，那么只要在 $m$ 个操作中找到一步即可排好序的决定性操作，其余的操作就不看了。

举个例子:


```
5 4
4 2 1 3 5
3 0.2
4 0.7
5 0.4
2 0.1
```

很明显，对于上面的数据，只有操作 $2,3$ 是 “决定性操作” ， 所以如果操作 $2$ 成功了，那么概率就是 $0.7$ ， 否则，如果操作 $2$ 未成功，那就用剩下的 $0.3$ 乘以 $0.4$ ，总概率就是 $0.82$

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,m;
int a[100005],ok_sort[100005];
double ans;
int main(){
	cin>>T;
	while(T--){
      ans=0.00;
		cin>>n>>m;
		for(int i=1; i<=n; i++){
			cin>>a[i]; 
			ok_sort[i]=a[i];
		}
		sort(ok_sort+1,ok_sort+n+1);//设置已经排序的数组
		int pos=0; // x
		for(int i=n; i>=1; i--){ // 找 x 的步骤
			if(a[i]!=ok_sort[i]){
				pos=i;
				break;
			}
		}
		while(m--){
			int r; double p;
			cin>>r>>p;
			if(r>=pos) ans+=(1-ans)*p; // 求概率
		}
		if(pos==0){ // 特判，如果先天就是升序，输出1
			cout<<1<<endl;continue;
		}
		printf("%.7lf\n",ans);
	}
}
```



---

## 作者：ctt2006 (赞：1)

首先，从后往前扫，找出第一个$a_i\neq i$的位置，记为$st$

从前往后扫，对于$r_i<st$的，选不选都没关系。

对于$r_i\ge st$的，至少有一个成功排序就会使整个序列被排序

考虑容斥，用所有情况减去$r_i\ge st$一个都不选的情况即可

即$ans = 1-\prod\limits_{r_i\ge st} {1-p_i}$

代码如下
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int t,n,m;
int a[100005],st;
inline int read() {
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int r[100005];
double p[100005];
int main () {
	t = read();
	while(t--) {
		n = read();m = read();
		int flag = 1;
		for(int i = 1;i <= n;i++) a[i] = read();
		for(int i = 1;i <= m;i++) {
			scanf("%d%lf",&r[i],&p[i]);
		} 
		for(int i = 1;i <= n;i++) flag = flag & (a[i] == i);
		if(flag) {
			puts("1.00000000");
			continue;
		}
		for(int i = n;i >= 1;i--) {
			if(a[i] != i) {
				st = i;
				break;
			}
		}
		double ans = 1;
		for(int i = 1;i <= m;i++) {
			if(r[i] < st) continue;
			if(ans == 0) ans = 1-p[i];
			else ans = ans * (1-p[i]);
		}
		printf("%.10lf\n",1-ans);
	}
	return 0;
}
```

---

## 作者：RockyYue (赞：1)

感谢管理大大审核~

# 解题思路

先记录下最后一个不对的位置，即符合 $a[i] \ne i$ 时的 $i_{max}$ ，记为 $k$，我们只需要判断 $a[1]$ 到 $a[k-1]$ 即可。

对于 $i \in [1,n]$，如果 $r[i] < k$，这个操作就没有用了。

否则，只要有一个就可以成功。

则答案为 $1-\Pi_{i=1}^n(r[i] \ge k) \times (1-p[i])$。

特别需要注意的是，初始就合法的情况需要特判、

# 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int a[N], r[N];
double p[N];
int main() {
	ios :: sync_with_stdio(0);
	int _;
	cin >> _;
	while (_--) {
		int n, m, k = -1;
		cin >> n >> m;
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
		}
		for (int i = 1; i <= m; ++i) {
			cin >> r[i] >> p[i];
		}
		for (int i = n; i; --i) {
			if (a[i] != i) {
				k = i;
				break;
			}
		}
		if (k == -1) {
			cout << 1 << '\n';
			continue;
		}
		double res = 1;
		for (int i = 1; i <= m; ++i) {
			if (r[i] < k) {
				continue;
			}
			res = res == 0 ? (1 - p[i]) : res * (1 - p[i]);
		}
		cout << fixed << setprecision(6) << 1 - res << '\n';
	}
	return 0;
}
```

Good Good 贺题，Day Day Up！！

---

## 作者：vectorwyx (赞：0)

由于影响的总是某段前缀，因此当多个事件同时发生时，它的效果与 $r$ 最大的那个事件的效果是相同的。也就是说最终得到的序列是否满足要求只与单个事件有关，我们只需要求出那些发生后能使原排列升序的事件，它们中只要有一个事件发生就能满足要求，概率为 1-这些事件均不发生的概率。

判断事件 $i$ 发生后能否使排列升序也很简单，只需要满足两个条件：$[r_{i}+1,n]$ 本来就有序，且 $max[1,r_{i}]\le a_{r_{i}+1}$。前一个条件需要先求出最长的升序的后缀，后一个条件则需要预处理出前缀最大值。

注意，如果原排列已经有序，需要输出 $1$。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define db double
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e5+5;
int a[N],r[N],pre[N];
db p[N];

void work(){
	int n=read(),m=read(),len=0;
	db ans=1.0;
	fo(i,1,n) a[i]=read(),pre[i]=max(pre[i-1],a[i]);
	fo(i,1,m) r[i]=read(),cin>>p[i];
	a[n+1]=2e9;
	while(len<n&&a[n-len]<=a[n-len+1]) len++;
	//cout<<"len="<<len<<endl;
	if(len==n){
		puts("1.0000000");
		return;
	}
	fo(i,1,m) if(n-r[i]+1<=len&&pre[r[i]]<=a[r[i]+1]) ans*=(1.0-p[i]);
	printf("%.7lf\n",1-ans);
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

