# Two Movies

## 题目描述

一个公司发行了两部电影。现在有 $n$ 位观众，每个人都会看一部这个公司的电影。

每位观众都会对其看的电影进行评分，分数 $a_i,b_i\in\{-1，0，1\}$。电影的总评分是看了此电影的观众对此电影的评分总和。公司的最终得分是这两部电影的总评分的较小值。

已知这些观众对两部电影的评价，你需要给每个人推荐一部电影，使公司的最终得分最大。求这个最大值。

## 样例 #1

### 输入

```
4
2
-1 1
-1 -1
1
-1
-1
5
0 -1 1 0 1
-1 1 0 0 1
4
-1 -1 -1 1
-1 1 1 1```

### 输出

```
0
-1
1
1```

# 题解

## 作者：Vct14 (赞：6)

[题意](https://www.luogu.com.cn/discuss/848640)。

如果一名观众对某部电影的评分大于另一部，那么推荐他去看他更看好的电影更优。

如果一名观众对两部电影的评分相同，那么他对两部电影的总评分贡献相同。我们将这个评分存到最后，然后增加小的、减少大的，让较小值尽量大。

```c++
#include<bits/stdc++.h>
using namespace std;

int a[200002];
int b[200002];
int c[200002];

int main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		for(int i=1; i<=n; i++) cin>>a[i]; 
		for(int i=1; i<=n; i++) cin>>b[i];
		int suma=0,sumb=0,s=0;
		for(int i=1; i<=n; i++){
			if(a[i]>b[i]) suma+=a[i];
			else if(a[i]<b[i]) sumb+=b[i];
			else if(a[i]!=0) c[++s]=a[i];
		}
		for(int i=1; i<=s; i++){
			if(suma>=sumb){
				if(c[i]==1) sumb++;
				else suma--;
			}
			else{
				if(c[i]==1) suma++;
				else sumb--;
			}
		}
		cout<<min(suma,sumb)<<"\n";
	}
	return 0;
}
```

---

## 作者：chatoudp (赞：3)

若一人对两部电影的看法不同，必然要让他对他看法较好的一部电影进行评论。

若看法相同，那我们就需要利用最后公司评分为两部电影的最小评分为结果这条信息。首先先处理看法不同的情况，再处理此情况：

因为评论评分较高的电影对最终评分无影响，评论评分较低的电影对最终评分则有影响。所以若看法为 $1$ 就让其评论评分较低的电影，若看法为 $-1$ 就让其评论评分较高的电影，若看法为 $0$ 则评论任何一个电影即可。这样可以让差评无影响，好评有影响。

### 接下来就是 AC 时间：
```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef long long ll;
int t,n,a[200005],b[200005];
vector<int> v; 
int main(){//'_' T_T ^_^
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int j=1;j<=n;j++) scanf("%d",&b[j]);
		v.clear();
		int f1=0,f2=0;
		for(int i=1;i<=n;i++)
			if(a[i]>b[i]) f1+=a[i];
			else if(b[i]>a[i]) f2+=b[i];
			else v.push_back(i);
		for(auto p:v)
			if(f1<f2){
				if(a[p]<0) f2+=b[p];
				else f1+=a[p];
			} 
			else{
				if(a[p]<0) f1+=a[p];
				else f2+=b[p];
			} 
		printf("%d\n",min(f1,f2));
	}
	
	return 0;
}

```

---

## 作者：gaomingyang101011 (赞：3)

## 思路

这是一道贪心题，我们在输入后需要判断一位观众对一个电影的评分大于另一部电影就让他对这一部电影做评价，如果他对这两部电影的评价相同的话，就先将他的评价保存下来，在处理完其他的评价后再处理对两部电影相同的评价。

在处理相同的评价时我们判断如果两个的评价都是 $-1$ 的话就将评分较大的电影的评分减一，如果都是 $1$ 的话就将评分较小的电影的评分加一。

## 代码

```cpp
#include<iostream>
using namespace std;
const int N=2*1e5+5;
int t;
int n;
int a[N],b[N];
int ansa,ansb;
int c[N],s;
int main(){
	cin>>t;
	while(t--){
		ansa=0,ansb=0,s=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) cin>>b[i];
		for(int i=1;i<=n;i++){
			if(a[i]>b[i]) ansa+=a[i];
			else if(b[i]>a[i]) ansb+=b[i];
			else c[++s]=a[i];
		}
		for(int i=1;i<=s;i++){
			if(c[i]<0){
				if(ansa>=ansb) ansa-=1;
				else ansb-=1;
			}
			else if(c[i]>0){
				if(ansa>=ansb) ansb+=1;
				else ansa+=1;
			}
		}
		cout<<min(ansa,ansb)<<endl;
	}
	return 0;
}
```

---

## 作者：HuangBarry (赞：3)

[原题CF1989C Two Movies](https://www.luogu.com.cn/problem/CF1989C)  
题意：给出 $n$ 个人对两部电影的评价，让你分配每个人对其中一部电影进行评价，使两部电影的最低评分最大化。  
做法：[贪心](https://baike.baidu.com/item/%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95/5411800)。  
分析：两种情况，一，$a_i \ne b_i$，显而易见，把高分的评给电影。二，$a_i = b_i$，再细分两种情况，分别是 $a_i = b_i = 1$ 和 $a_i = b_i = -1$，可以纪录下这两种情况出现的次数，最后进行统一处理，也就是高分减去，低分加上。  
代码如下：  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+25;
int t,a[N],b[N],n;
int main(){
	cin>>t;
	while(t--){
		int movie1=0/*电影一的评分*/,movie2=0/*电影二的评分*/,sumfu1=0/*a[i]=b[i]=-1出现的次数*/,sum1=0/*a[i]=b[i]=1出现的次数*/;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i];
		for(int i=1;i<=n;i++)
			if(a[i]>b[i]) movie1+=a[i];
			else if(a[i]<b[i]) movie2+=b[i];
			else if(a[i]==1) sum1++;
			else if(a[i]==-1) sumfu1++;
		while(sum1--)
			if(movie1<=movie2) movie1++; //低分加上
			else movie2++;
		while(sumfu1--)
			if(movie1>=movie2) movie1--; //高分减去
			else movie2--;
		cout<<min(movie1,movie2)<<endl; //取最低分
	}
	return 0;
}
```  
[AC 记录](https://www.luogu.com.cn/record/164093838)

---

## 作者：X____ (赞：2)

设当前第一部电影评分为 $x$，第二部电影评分为 $y$。

首先想到分情况讨论，对于 $a_{i} = b_{i}$，假设当前 $x = y$，我们选择 $x$ 还是 $y$ 似乎对于答案没有影响，但是如果后面出现 $a_{i} \ne b_{i}$ 这样的情况这么做就不成立了。因为我们无法知道上一步 $a_{i}=b_{i}$ 时的选择对当前的选择是否最优的。

这也就说明了 $a_{i} = b_{i}$ 会对后面 $a_{i} \ne b_{i}$ 的情况产生影响，所以我们将 $a_{i} \ne b_{i}$ 的情况提前处理。



 对于 $a_{i} \ne b_{i}$ 的情况，显然是谁大就选择谁最优。对于另外一种情况我们让评分大的尽量小，小的尽量大即可。

```cpp
F(i, 1, n) {
	if(a[i] > b[i]) x += a[i];
	if(b[i] > a[i]) y += b[i];
	if(a[i] == b[i]) c[++m] = a[i];
}
F(i, 1, m) {
	if(c[i] == 1) x < y ? x++ : y++;
	if(c[i] == -1) x < y ? y-- : x--;
}
cout << min(x, y) << "\n";
```

---

## 作者：a_girl (赞：1)

[CF1989C Two Movies](https://www.luogu.com.cn/problem/CF1989C)

## 题意
有 $n$ 名观众，每人对 $2$ 部电影，都有不同的评价，我们需要给每个观众推荐一部电影，使公司的最终得分最大，求这个最大值是多少。

## 思路
本题考虑贪心。

如果观众对两部电影评价不同，我们就哪个电影的评价大谁加。

如果一样，我们到最后再考虑，我们就综合考虑，两部电影的评价谁更小谁加，另外一个减少。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005],b[200005],c[200005];
int main()
{
	int t;
	cin>>t;
	while(t--)//多组数据 
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i]; 
		for(int i=1;i<=n;i++) cin>>b[i];
		int aa=0,bb=0,id=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]>b[i]) aa+=a[i];
			else if(a[i]<b[i]) bb+=b[i];//如果不一样，就谁大谁加 
			else if(a[i]!=0)
			{
				id++;
				c[id]=a[i];
			}
		}
		for(int i=1;i<=id;i++)
		{
			if(aa>=bb)
			{
				if(c[i]==1) bb++;
				else aa--;
			}
			else
			{
				if(c[i]==1) aa++;
				else bb--;
			}//否则就一个一个判断 
		}
		cout<<min(aa,bb)<<endl;
	}
	return 0;谢谢观看 
}
```

---

## 作者：__galaxy_1202__ (赞：0)

## 解题思路：
贪心题，第 $i$ 个人对哪个公司的贡献大就让他对哪个公司评价。  
如果对两个公司的评价一样且不为 $0$，就看他的评价是 $-1$ 还是 $1$，分数为 $-1$ 的贡献给高分公司，分数为 $1$ 的贡献给低分公司，让两个公司分数尽量平衡。
## CODE:
```cpp
#include <iostream>
using namespace std;
int t, n, a[200001], b[200001], c[200001];
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        int ansa = 0, ansb = 0, cur = 0;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        for (int i = 1; i <= n; i++)
        {
            if (a[i] > b[i]) ansa += a[i];
            else if (a[i] < b[i]) ansb += b[i];
            else if (a[i] != 0) c[++cur] = a[i];
        }
        for (int i = 1; i <= cur; i++)
        {
            if (ansa >= ansb)
            {
                if (c[i] == 1) ansb++;
                else ansa--;
            }
            else
            {
                if (c[i] == 1) ansa++;
                else ansb--;
            }
        }
        cout << min(ansa, ansb) << '\n';
    }
    return 0;
}
```

---

## 作者：RaymondOccam (赞：0)

### 题目传送门
[Codeforces-1989C](https://codeforces.com/problemset/problem/1989/C)
### 思路
贪心题。

因为题目中已经说明，最后公司的得分是两部电影得分中的**较小值**，所以我们要想让两个电影总分中的最小值不过小，可以在输入的时候把这名观众对两部电影的评价作比较，哪一个大，就推荐这名观众看哪部电影。

如果评价相同呢？

对于这种情况，我们可以把这两条评价保存起来。而为了节省空间，我们只需要存储其中一条评价即可，因为两条评价相同，所以存两条相同的评价就占用了 $2$ 倍的空间。到处理完的时候，我们先看评分为 $-1$ 的情况，我们把这条评分给到目前评分较大的那部电影上，减少大的评分；而对于评分为 $1$ 的情况，我们把这条评分给到目前评分较小的那部电影上，增加小的评分。这样就保证了使最小评分尽可能地大。

### 代码实现
[AC记录](https://codeforces.com/problemset/submission/1989/270887566)

终于要实现代码了~~~

我个人认为思路应该很详细了吧？下面给出代码，不懂的看上面的思路：

```cpp
#include <iostream>
#include <cmath>
#define ll long long
#define MAXN 200050
using namespace std;
ll t;
ll n;
struct Node
{
    ll a, b;
} l[MAXN], res;
ll save[MAXN];
ll pos;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t--)
    {
        res.a = 0, res.b = 0, pos = 0; // 初始化
        cin >> n;
        for (ll i = 1; i <= n; i++)
            cin >> l[i].a;
        for (ll i = 1; i <= n; i++)
        {
            cin >> l[i].b;
            if (l[i].a == l[i].b)
                save[++pos] = l[i].a; // 存储评价
            else if (l[i].a > l[i].b)
                res.a += l[i].a;
            else
                res.b += l[i].b;
        }
        for (ll i = 1; i <= pos; i++)
            if (save[i] == 1)
                if (res.a < res.b)
                    res.a++;
                else
                    res.b++;
            else if (save[i] == -1)
                if (res.a < res.b)
                    res.b--;
                else
                    res.a--;
        cout << min(res.a, res.b) << '\n'; // 最小值
    }
    return 0;
}
```

---

## 作者：donnieguo (赞：0)

## 思路

考虑贪心。

记 $s1,s2$ 分别表示第一部和第二部电影的总评分。

对于每一位观众的评价，如果该观众对 $2$ 部电影的评分不同，显然让其评价其评分较高的那部更优。

对于对 $2$ 部电影评分相同的观众来说，因为我们要使评分的最小值尽可能大，所以我们要分情况考虑：

- 对于评分为 $-1$ 的观众，让其评价 $\max(s1,s2)$；

- 对于评分为 $0$ 的观众，让其评价哪一部电影对最终的 $s1$ 和 $s2$ 都不会有影响；

- 对于评分为 $1$ 的观众，让其评价 $\min(s1,s2)$。

这样我们就可以使得 $\max(s1,s2)$ 和 $\min(s1,s2)$ 尽量平均（即评分的最小值尽可能大）。

当然，我们要使用以上方法之前需要先忽略所有评分相同的观众，计算出初始的 $s1$ 和 $s2$，最后再使用以上方法考虑评分相同的观众。（具体见代码）

- $\text{PS}$：看到其他的题解都是将相同的评分存储起来，其实不用，只用判断一下当前的 $a_i$ 是否等于 $b_i$ 即可。

## AC代码

```cpp
#include <iostream>
#define N 200010
using namespace std;

int T, n, a[N], b[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--) {
		int s1 = 0, s2 = 0; //多测记得清空
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		for (int i = 1; i <= n; i++)
			cin >> b[i];
		for (int i = 1; i <= n; i++) {
			if (a[i] > b[i]) //先计算出评分不同的观众对s1和s2的影响
				s1 += a[i];
			else if (a[i] < b[i])
				s2 += b[i];
		}
		for (int i = 1; i <= n; i++) {
			if (a[i] == b[i]) { //再考虑评分相同的观众
				if (a[i] == -1)
					s1 >= s2 ? s1-- : s2--;
				else if (a[i] == 1)
					s1 > s2 ? s2++ : s1++;
			}
		}
		cout << min(s1, s2) << '\n';
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

## 思路分析

贪心，想必大家都知道怎么贪吧？能加就一定不减。尽量给小的加，实在加不了就选大的减。不过有一个小细节：左右相等的怎么处理？

这个东西是确确实实会受到后面的影响的，不能够乱选。因此，我们考虑将这一部分视作“听用牌”，放到最后进行考虑。显然，依然是套上面的贪心方式。

代码并不长。如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],b[200005],sm[2],ans[2];
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n; sm[0]=sm[1]=ans[0]=ans[1]=0;
		for(int i=1;i<=n;++i)cin>>a[i];
		for(int i=1;i<=n;++i)cin>>b[i];
		for(int i=1;i<=n;++i){
			if(!a[i]&&!b[i]) continue;
			if(a[i]==b[i]) sm[(a[i]!=1)]++;
			else if(a[i]>b[i]) ans[0]+=a[i];
			else ans[1]+=b[i];
		}
		while(sm[0]--) ans[(ans[0]>ans[1])]++;
		while(sm[1]--) ans[(ans[0]<ans[1])]--;
		cout<<min(ans[0],ans[1])<<endl;
	}
}
```

---

## 作者：icaijy (赞：0)

# 思路

注意到数据范围并不小，因此只能使用线性的做法，考虑贪心。

当一个观众对两个电影打分**不同**时，我们可以直接让他看打分高的电影，此时是最优解。

当一个观众对两个电影打分**相同**时，则分类讨论。若两电影均为 $0$ 分，就不用处理。若两电影评分都为 $1$，就先把它存起来。因为我们无法判断当前给哪个电影加分会是最优（当前评分较低，的到后面可能就是较高的了）。同理，两电影评分均为 $-1$ 的也存下来。

当我们处理完所有数之后，就来解决两电影评分相同的问题了。其实很简单，只需要让评分较小的电影加一，评分较高的电影减一就可以。因为我们只关心评分较小的电影，只有它评分高了才有用。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,num;
vector<short> a;//存第一部
vector<short> b;//存第二部

int cnt1,cnt2,cnta,cntb;//两个都为1，-1的个数，电影评分
signed main() {
	cin>>t;
	while (t--){
		cnt1=cnt2=cnta=cntb=0;
		vector<short>().swap(a);
		vector<short>().swap(b);
      //多测记得清空
		cin>>n;
		for (int i=0;i<n;i++) cin>>num,a.push_back(num);
		for (int i=0;i<n;i++) cin>>num,b.push_back(num);
		for (int i=0;i<n;i++){
			if (a[i]==b[i]){//相同时
				if (a[i]==1) cnt1++;
				else if(a[i]==-1) cnt2++;
			}
			else a[i]>b[i]?cnta+=a[i]:cntb+=b[i];//不同哪个大加哪个
		}
		while (cnt1--) cnta<cntb?cnta++:cntb++;//处理相同的
		while (cnt2--) cnta<cntb?cntb--:cnta--;
		cout<<min(cnta,cntb)<<endl;
	}
}
```

---

## 作者：IOI_official (赞：0)

# CF1989C Two Movies 题解

## 思路：

考虑贪心。

这题分两种情况：

1. $a_i\ne b_i$，这时选最大的加为最优。
  
2. $a_i= b_i$，用一个数组先存起来，最后再将小于零的加给大的，大于零的加给小的，使小的尽量大。
  

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[11451419],b[11451419],c[11451419],aa,bb,ii;
int maxn,minn;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		bb=aa=0;
		ii=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		for(int i=1;i<=n;i++){
			if(a[i]>b[i]){
				aa+=a[i];
			}
			else if(b[i]>a[i]){
				bb+=b[i];
			}
			else{
				c[++ii]=a[i];
			}
		}
		for(int i=1;i<=ii;i++){
			if(c[i]>0){
				if(aa>=bb) bb+=1;
				else aa+=1;
			}
			if(c[i]<0){
				if(aa>=bb) aa-=1;
				else bb-=1;
			}
		}
		cout<<min(aa,bb)<<'\n';
	}
	return 0;
}
```

---

## 作者：PengDave (赞：0)

# solution
考虑贪心，当 $a_i\ne b_i$ 时，若 $a_i$ 大，则让 $1$ 号影院的分值增加，反之让 $2$ 号影院分值增加。若 $a_i=b_i$，为了让两影院分值的最小值最大，我们要尽量让它们更加接近，让大的减少，小的变大。
# code
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<sstream>
#include<cctype>
#include<vector>
#include<bitset>
using namespace std;
int a[200010],b[200010];
int main(){
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		int ans1=0,ans2=0,cnt1=0,cnt2=0;
		for(int i=1;i<=n;i++){
			if(a[i]>b[i]){
				ans1+=a[i];
			}else if(a[i]<b[i]){
				ans2+=b[i];
			}else if(a[i]==-1){
				cnt2++;
			}else if(a[i]==1){
				cnt1++;
			}
		}
		while(cnt1--){//小的增加
			if(ans1<ans2){
				ans1++;
			}else{
				ans2++;
			}
		}
		while(cnt2--){//大的减少
			if(ans1>ans2){
				ans1--;
			}else{
				ans2--;
			}
		}
		cout<<min(ans1,ans2)<<"\n";
	}
	cout<<flush;
	return 0;
}
```

---

## 作者：xcms (赞：0)

是一道贪心题目。为了使最小值最大，需要使用分类讨论的方法。

用 $cnt1$ 来表示第一部电影的得分，$cnt2$ 来表示第二部电影的得分。

$a_i$ 和 $b_i$ 有 $2$ 种情况：

* $a_i\not=b_i$ 这种情况直接加在计数器里就可以，如果 $a_i>b_i$ 就把 $cnt1$ 加上 $a_i$，否则就把 $cnt2$ 加上 $b_i$。
* $a_i=b_i$ 首先如果 $a_i=1$，为了使最小值最大，显然要加给 $cnt1$ 和 $cnt2$ 中较小的那个；如果 $a_i=0$，那把它加给谁结果都不会受影响；如果 $a_i=-1$，肯定要让比较大的计数器减去 $1$。

然后根据上面的思路可以写出以下代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int t,n,a[N],b[N];
signed main(){
    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++)cin>>b[i];
        int cnt1=0,cnt2=0,t1=0,t2=0;
        for(int i=1;i<=n;i++){
            if(a[i]>b[i])cnt1+=a[i];
            else if(a[i]<b[i])cnt2+=b[i];
            else{
                if(a[i]==1){
                    if(cnt1<cnt2)cnt1++;
                    else cnt2++;
                }
                if(a[i]==-1){
                    if(cnt1>cnt2)cnt1--;
                    else cnt2--;
                }
            }
        }
        cout<<min(cnt1,cnt2)<<"\n";
    }
    return 0;
}

```

结果，样例都没有通过，我么可以拿第一组样例模拟一下。

```
2
-1 1
-1 -1
```

这组样例的正确输出是 $0$，而以上的代码输出的是 $-1$。

在 $i=1$ 时，$a_i$ 与 $b_i$ 是相等的，这时候 $cnt1$ 不大于 $cnt2$，所以 $cnt2$ 减去 $1$，变成 $-1$。

在 $i=2$ 时，$a_i$ 与 $b_i$ 不相等，所以直接就把 $cnt1$ 加上了 $1$。

最后输出 $\min(-1,1)=-1$。

所以要改变策略，以上的程序是根据现在的 $cnt1$ 与 $cnt2$ 来判断，然而以后可能会有新的 $a_i$ 或 $b_i$ 加上去。因此在运行时，先把 $a_i\not= b_i$ 时的操作全部执行完毕，再进行 $a_i=b_i$ 时的操作。

[AC](https://www.luogu.com.cn/record/164460308) 代码如下。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int t,n,a[N],b[N];
signed main(){
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++)cin>>b[i];
		int cnt1=0,cnt2=0,t1=0,t2=0;
		for(int i=1;i<=n;i++){
			if(a[i]>b[i])cnt1+=a[i];
			else if(a[i]<b[i])cnt2+=b[i];
			else{
				if(a[i]==1)t1++;
				if(a[i]==-1)t2++;
			}
		}
		for(int i=1;i<=t1;i++){
			if(cnt1<cnt2)cnt1++;
			else cnt2++;
		}
		for(int i=1;i<=t2;i++){
			if(cnt1>cnt2)cnt1--;
			else cnt2--;
		}
		cout<<min(cnt1,cnt2)<<"\n";
	}
	return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

蒟蒻居然半个小时场切了 *1400！

首先，我们发现评分一大一小的情况肯定投给分大的。

其次那么我们只剩下两个 $1$ 或两个 $-1$ 的情况了。在此，我们设有 $A$ 个人的投票是两个 $1$，$B$ 个人投票时两个 $-1$，经过先前的操作第一部电影已经获得了 $C$ 分，第二部电影获得了 $D$ 分。

那么我们就考虑二分答案，设二分到最终得分为 $x$，那么我们就可以暴力枚举有几人给第一部电影投了 $1$（设有 $i$ 个人），那么我们也可以进而算出第二部电影有几人投了 $1$（$A-i$ 人），然后我们就可以发现在这种情况下，我们可以容纳 $((i+C)-x)+((A-i+D)-x)$ 人投 $-1$，所以我们只用判断这个值是否 $\ge B$ 即可，如果行那么就令 $l=x$，否则 $r=x$。

---

## 作者：qhr2023 (赞：0)

## 思路

贪心。

如果 $a_i \ne b_i$，那么一定选评分高，否则不会提高任何电影的评分。

若相等，当都为 $0$ 时，怎样分配都不会对答案产生影响，忽略即可，我们分别记录一下评分为 $1$ 和 $-1$ 的个数，在处理完评分不一样的人之后，将 $1$ 评给评分低的，将 $-1$ 评给评分高的。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T, n, a[200005], b[200005];
int main() {
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i=1; i<=n; i++)
			cin >> a[i];
		for (int i=1; i<=n; i++)
			cin >> b[i];
		int x=0, y=0, s1=0, s2=0;
		for (int i=1; i<=n; i++) 
			if (a[i]>b[i])
				x+=a[i];
			else if (a[i]<b[i])
				y+=b[i];
			else 
				s1+=(a[i]==1),
				s2+=(a[i]==-1);
		while (s1--)
			x<y?x++:y++;
		while (s2--) 
			x>y?x--:y--;
		cout << min(x, y) << '\n';
	}
	return 0;
}	
```

---

## 作者：w9095 (赞：0)

[CF1989C Two Movies](https://www.luogu.com.cn/problem/CF1989C)

贪心。如果某人对两部电影评分不一样，显然取评分高的那一个。如果是 $1$ 和 $0$ 或 $1$ 和 $-1$，那么显然取 $1$。如果是 $0$ 和 $-1$，显然取 $0$。

接下来，讨论评分一样的情况。对于 $0$ 和 $0$，取哪一个都没有影响，直接忽略。对于 $1$ 和 $1$，我们记录这种人的个数，在处理完评分不一样的人之后统一处理。由于我们要使最小值最大，所以优先将这种人的增加评分给较小的一部电影。否则不会影响最小值，显然不优。

对于 $-1$ 和 $-1$，同理，我们记录这种人的个数，在处理完评分不一样的人之后统一处理。由于我们要使最小值最大，所以优先将这种人的减少评分给较大的一部电影。否则会减小最小值，显然不优。

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,a[300000],b[300000];
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	long long x=0,y=0,pf=0,nf=0;
	   	scanf("%lld",&n);
	   	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	   	for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
	   	for(int i=1;i<=n;i++)
	   	    if(a[i]>b[i])x+=a[i];
	   	    else if(a[i]<b[i])y+=b[i];
	   	    else if(a[i]==1&&b[i]==1)pf++;
	   	    else if(a[i]==-1&&b[i]==-1)nf++;
	   	while(pf)
	   	   {
	   	   	if(x<=y)x++;
	   	   	else y++;
	   	   	pf--;
		   }
		while(nf)
	   	   {
	   	   	if(x>=y)x--;
	   	   	else y--;
	   	   	nf--;
		   }
		printf("%lld\n",min(x,y));
	   }
	return 0;
} 
```

---

## 作者：technopolis_2085 (赞：0)

题意：给出 $n$ 个对给两部电影评分，现在让你规划这 $n$ 个人分别给谁评分，使得这两部电影的较低分最大化。

分析：

设第一部电影的评分为 $sum1$，第二部电影的评分为 $sum2$。

将 $a_i$ 和 $b_i$ 分情况考虑：


- $a_i$ 等于 $b_i$。这时候给谁评分都一样（这个时候我们无法确定这个人给哪部电影评分，所以到最后评分）。设两个变量 $p$ 和 $m$。 $p$ 代表都是 $1$ 的个数，$m$ 代表都是 $-1$ 的个数。如果 $a_i$ 等于 $1$，那么 $p$ 变量加 $1$，如果 $a_i$ 等于 $-1$，$m$ 加 $1$。

- 如果 $a_i$ 和 $b_i$ 不一样，那么如果 $sum1+a_i ≤ sum2+b_i$，那么给第一部电影评分，否则向第二部电影评分。

此时，我们把确定能评分的人都评完了，此时可能还剩余一些当时不能评分的，即 $p$ 和 $m$，那么这个时候以 $p$ 为例：

如果 $sum1 ≤ sum2$，那么给第一部电影评分，否则给第二部。总共做 $p$ 次。

反之，每次给评分较高的减 $1$，做 $m$ 次。

最后取 $sum1$ 和 $sum2$ 的较小值即为答案。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=2e5+10;
int a[maxn],b[maxn];

void solve(){
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++) scanf("%d",&b[i]);

	int sum1=0,sum2=0;
	int m1=0,p1=0;
	for (int i=1;i<=n;i++){
		if (a[i]==-1&&b[i]==-1) m1++;
		else if (a[i]==-1&&b[i]!=-1) sum2+=b[i];
		else if (a[i]!=-1&&b[i]==-1) sum1+=a[i];
		else{
			if (a[i]==1&&b[i]==1) p1++;
			else{
				if (a[i]==1) sum1+=a[i];
				else sum2+=b[i];
			}
		}
	}
	
	for (int i=1;i<=p1;i++){
		if (sum1<sum2) sum1++;
		else sum2++;
	}
	
	for (int i=1;i<=m1;i++){
		if (sum1<sum2) sum2--;
		else sum1--;
	}
	
	printf("%d\n",min(sum1,sum2));
}

int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
	return 0;
}
```

---

## 作者：zg_ji (赞：0)

## 题目分析

求最小值，一眼贪心。

我们要使得分的最小值最大的话，我们需要将得分最小值与最大值的分差无限缩小就可以了。

答题思路就是，用两个数，分别存 $a_{i}$ 比 $b_{i}$ 大和 $b_{i}$ 比 $a_{i}$ 大。如果他们相等的时候，我们先不处理，等到最后再去判断，我需要将大的值缩小，小的值增大即可。要注意题目中说明分数只有三种情况。

## Code

```
#include<bits/stdc++.h>
const int N=2e5+100;
using namespace std;

int T;
int n;
int ans;
int anss;
int cnt[N];//计数数组 
int a[N],b[N];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)
	{
		int yu=0;
		ans=0,anss=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];//输入的值会覆盖先前的 
		for(int i=1;i<=n;i++) cin>>b[i];
		for(int i=1;i<=n;i++)
		{
			if(a[i]>b[i]) ans+=a[i];
			if(b[i]>a[i]) anss+=b[i];
			if(a[i]==b[i]) cnt[++yu]=a[i];//cnt[++yu]=b[i];
		}
		for(int i=1;i<=yu;i++)
		{
//			if(ans>=anss) ans--;
//			else anss++;
			//记得判断cnt数组中的数的正负
			if(cnt[i]<0)//if(cnt[i]==-1)
			{
				if(ans>=anss) ans--;
				else anss--;
			}
			else if(cnt[i]>0)//if(cnt[i]==1)
			{
				if(ans>=anss) anss++;
				else ans++;
			}
		}
		cout<<min(anss,ans)<<'\n';
	}
	
	return 0;
	
}
```

~~顺利完结~~

---

## 作者：Junior_Young (赞：0)

~~萌新第一次写题解，求过~~

此题正解就是贪心。

很明显：
1. 如果第 $i$ 个人顶第一部（ $a_i=1$ ）而不顶第二部，那一定给他推荐第一部，反之亦然；
1. 如果他踩第一部（ $a_i=-1$ ）却不踩第二部，那一定给他推荐第二部，反之亦然。

所以，我们能写出这样的程序：
```cpp
for(int i=1;i<=n;i++)
{
	if(a[i]>b[i]) al+=a[i];
	else if(a[i]<b[i]) bt+=b[i];
}
```

那如果他既顶第一部又顶第二部或者两部都踩怎么办呢？

显然，
> 公司的最终得分是这两部电影的总评分的较小值。

所以两者都顶时，把暂时评分小者顶上去；两者都踩时，踩评分大的（因为耐踩）。

上代码：
```cpp
const int N=2e5+5;
int a[N],b[N];
bool flag[N];
void Work()
{
	int n,al=0,bt=0;
	cin >> n;
	for(int i=1;i<=n;i++)
		flag[i]=1;
	for(int i=1;i<=n;i++)
		cin >> a[i];
	for(int i=1;i<=n;i++)
		cin >> b[i];
	for(int i=1;i<=n;i++)
	{
		if(a[i]>b[i]) al+=a[i];
		else if(a[i]<b[i]) bt+=b[i];
		else flag[i]=0;
	}
	for(int i=1;i<=n;i++)
	{
		if(flag[i]) continue;
		if(a[i]==1)
			if(al<bt) al++;
			else bt++;
		if(a[i]==-1)
			if(al>bt) al--;
			else bt--;
	}
	cout<<min(al,bt)<<'\n';
}
```

---

