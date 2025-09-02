# Dress'em in Vests!

## 题目描述

The Two-dimensional kingdom is going through hard times... This morning the Three-Dimensional kingdom declared war on the Two-dimensional one. This (possibly armed) conflict will determine the ultimate owner of the straight line.

The Two-dimensional kingdom has a regular army of $ n $ people. Each soldier registered himself and indicated the desired size of the bulletproof vest: the $ i $ -th soldier indicated size $ a_{i} $ . The soldiers are known to be unpretentious, so the command staff assumes that the soldiers are comfortable in any vests with sizes from $ a_{i}-x $ to $ a_{i}+y $ , inclusive (numbers $ x,y>=0 $ are specified).

The Two-dimensional kingdom has $ m $ vests at its disposal, the $ j $ -th vest's size equals $ b_{j} $ . Help mobilize the Two-dimensional kingdom's army: equip with vests as many soldiers as possible. Each vest can be used only once. The $ i $ -th soldier can put on the $ j $ -th vest, if $ a_{i}-x<=b_{j}<=a_{i}+y $ .

## 说明/提示

In the first sample you need the vests' sizes to match perfectly: the first soldier gets the first vest (size 1), the third soldier gets the second vest (size 3). This sample allows another answer, which gives the second vest to the fourth soldier instead of the third one.

In the second sample the vest size can differ from the desired size by at most 2 sizes, so all soldiers can be equipped.

## 样例 #1

### 输入

```
5 3 0 0
1 2 3 3 4
1 3 5
```

### 输出

```
2
1 1
3 2
```

## 样例 #2

### 输入

```
3 3 2 2
1 5 9
3 5 7
```

### 输出

```
3
1 1
2 2
3 3
```

# 题解

## 作者：lsy_41 (赞：6)

### 题目分析

一、关于输入输出的解释

输入的第一行是人的数量 $n$ ，衣服的数量 $m$ ，以及衣服的弹性 $x$ ， $y$ 。

第二行为 $a_i$ 。

第三行为 $b_i$ 。

输出的第一行为最多有多少人能买到合适的衣服。

接下来每行为匹配的人的编号，以及对应的衣服的编号。

二、思路：

思考之后不难发现，如果一个人选了最不合适他的衣服，但在弹性内他能穿上，那么其他人就更有可能选到能穿的衣服，翻译过来就是，对于一个 $a_i$ 找到能匹配的最小的 $b_i$ ，最后记录结果就得到了解。

三、实现：

实现起来就很容易了，只需要用两个指针，$ia$ ， $ib$ ，分别表示目前到了哪个人，哪件衣服，由于满足 $B$ 单增，通过 $ib$ 向后找到的第一个能穿上的一定是最小的，也就是上述的思路。

四、细节：

给定的大小都是严格单增的。

其他的细节注释在了代码里，~~本人认为写的还是挺好看的（逃~~。

------------

上代码啦：

```cpp
#include <bits/stdc++.h>
#define maxn 100005
using namespace std;
int n, m, x, y, cnt; //n:人的数量，m:衣服的数量，x,y:弹性，cnt:匹配的数量
int A[maxn], B[maxn]; //A:每个人希望的大小，B:衣服的大小
int ansx[maxn], ansy[maxn]; //记录答案的匹配
int main() {
	cin >> n >> m >> x >> y;
	for (int i = 1; i <= n; i++)
		cin >> A[i];
	for (int i = 1; i <= m; i++)
		cin >> B[i];
	int ia = 1, ib = 1; //两个指针，ia为当前的人，ib为当前的衣服
	while (ia <= n && ib <= m) { //如果人没有走完，衣服也没被买完
		while (B[ib] + x < A[ia]) //如果当前的人穿不了，就向后找更大的
			ib++;
		//这里需要注意一下，如果不能穿，一定是太小了，而不会是太大了
		if (ia <= n && ib <= m && A[ia] - x <= B[ib] && A[ia] + y >= B[ib]) {
			//注意看是否还在范围内，因为可能当前的人已经没有合适的衣服了
			ansx[++cnt] = ia; //记录答案
			ansy[cnt] = ib;
			ib++;
		}
		ia++;
	}
	cout << cnt << endl;
	for (int i = 1; i <= cnt; i++)
		cout << ansx[i] << " " << ansy[i] << endl; //输出答案
	return 0;
}
```
至此就做完啦，看都看完了，应该也学会了吧，代码要自己写哦，~~点个赞再走吧~~。

完结撒花！

---

## 作者：Erinyes (赞：2)

## Part 1：题目分析
题目的意思是让我们匹配最多的 $b_i$，最优的情况就是把每一个可以匹配的 $a_i$ 都匹配它最小的 $b_i$，这样就可以将更多的 $b_i$ 匹配上，且不影响之前的匹配。

## Part 2：题目求解
按照 Part 1 的思路，我们应该将 $a$ 数组和 $b$ 数组排序，这样才能保证每一个 $a_i$ 往后的第一个能匹配上的 $b_i$ 是最小的。

但题目给出的 $a$ 数组和 $b$ 数组是单调递增的，所以不需要我们自己排序。

接下来便是进行计算了。

我使用了两个下标指针 $pa$ 和 $pb$，分别表示当前匹配到的 $a$ 数组和 $b$ 数组的位置。

类似于单调队列的方法，每次找到一个 $a_{pa}$，就应该把不能匹配它的 $b_{pb}$ 扔掉。

```cpp
while(b[pb]<a[pa]-x) pb++;
```

现在相当于我们已经找到了一个合适的 $pa$ 和 $pb$，如果它们可以匹配，就应该将它们记录下来。

我用了一个结构体来记录答案。

```cpp
if(pa<=n && pb<=m && b[pb]>=a[pa]-x && b[pb]<=a[pa]+y){ //可以匹配
    ans[++cnt]=(node){pa,pb}; //记录答案
    pb++; //将b数组的指针向后移一位，表示这个b[pb]已经匹配过了
}
```
最后，不管这个 $a_{pa}$ 有没有匹配上，都要把 $pa$ 向后移一位，否则就会影响已经匹配的 $pa$。
```cpp
pa++;
```
## Part 3：Code
```cpp
#include<bits/stdc++.h>
#define maxn 100005
using namespace std;
struct node{int x,y;}ans[maxn];
int n,m,cnt;
int x,y;
int a[maxn],b[maxn];
int main(){
    scanf("%d %d %d %d",&n,&m,&x,&y);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=m;i++) scanf("%d",b+i);
    int pa=1,pb=1;
    while(pa<=n && pb<=m){
        while(b[pb]<a[pa]-x) pb++;
        if(pa<=n && pb<=m && b[pb]>=a[pa]-x && b[pb]<=a[pa]+y){ //可以匹配
            ans[++cnt]=(node){pa,pb}; //记录答案
            pb++; //将b数组的指针向后移一位，表示这个b[pb]已经匹配过了
        }
        pa++;
    }
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;i++) printf("%d %d\n",ans[i].x,ans[i].y);
    getchar(); getchar();
    return 0;
}
```


---

## 作者：Legendre_Gauss (赞：2)

本题的大意就是有n个人，有m个背心，当背心大小b[j]满足a[i]-x<=b[j]<=a[i]的时候，就可以满足配对。   
那我们考虑先跑一遍算出最大的匹配数量，最跑一遍对匹配进行输出。  
那么本题n,m<=10^5,所以O(n^2)不是标准算法，那没考虑两个指针，一个指a[],一个指b[],每当满足条件就向后推进。  

代码如下：
```
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;

int n,m;
int x,y;
int ans=0;
int a[100500],b[100500];

void init()
{
	scanf("%d%d%d%d",&n,&m,&x,&y);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)scanf("%d",&b[i]);
}

void work()
{
	int h1=1,h2=1;	
	while (h1<=n && h2<=m)
	{
		if(a[h1]-x<=b[h2] && a[h1]+y>=b[h2])
			ans++,h1++,h2++;
		else if(a[h1]-x>=b[h2])h2++;
		else if(a[h1]+y<=b[h2])h1++;
	}
	cout<<ans<<endl;
	h1=h2=1;
	while (h1<=n && h2<=m)
	{
		if(a[h1]-x<=b[h2] && a[h1]+y>=b[h2])
		{
			printf("%d %d\n",h1,h2);
			h1++,h2++;
		}
		else if(a[h1]-x>=b[h2])h2++;
		else if(a[h1]+y<=b[h2])h1++;
	}
	return;
}

int main()
{
	init();
	work();
	return 0;
}

```
本题就是这样的模拟。。。

---

## 作者：cqbztz2 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF161A)

# 思路：

先将 $ a , b $ 排个序，然后枚举 $ a[i] $ 和 $ b[j] $ 如果能适配就 ` i++,j++ `，如果 ` b[j] < a[i] - x ` 那么说明 $ b[j] $ 对后面的 $ a[i] $ 也都不能适配（因为我们已经将 $ a $ 按从小到大排了）就 ` j++ `，否则 ` i++ `。

# 代码：

```
    #include<bits/stdc++.h>
    using namespace std;
    int n,m,x,y,ans[100005],j=1,cnt;
    struct nobe{
        int s,id;
    }a[100005],b[100005];
    bool cmp(nobe x,nobe y){
        return x.s<y.s;
    }
    int main(){
        cin>>n>>m>>x>>y;
        for(int i=1;i<=n;i++){
            cin>>a[i].s;
            a[i].id=i;
        }
        for(int i=1;i<=m;i++){
            cin>>b[i].s;
            b[i].id=i;
        }
        sort(a+1,a+n+1,cmp);
        sort(b+1,b+m+1,cmp);
        for(int i=1;i<=n;i++){
            while(b[j].s<a[i].s-x&&j<=m){
                j++;
            }
            if(a[i].s-x<=b[j].s&&a[i].s+y>=b[j].s){
                ans[i]=j;
                j++;
                cnt++;
            }
            if(j>m){
                break;
            }
        }
        cout<<cnt<<endl;
        for(int i=1;i<=n;i++){
            if(ans[i]!=0){
                cout<<i<<" "<<ans[i]<<endl;
            }
        }
        return 0;
    }
```


---

## 作者：huhaoming2011 (赞：0)

# 题解：CF161A Dress'em in Vests!
## 题目大意
题目翻译十分详细。

~~懒，不想写。~~
## 分析
这道题目的匹配其实十分简单。

让每个人穿上尽可能不合适（更紧）却因弹性合适的衣服，这样就可以让往后的人尽可能地有衣服穿。以此，我们双指针，一个指向衣服，另一个指向人，模拟即可。

细节：当你让衣服尺寸在弹性下大于人有也要判断，否则会有尺寸太大的情况（这并不合法）。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 100;
int n, m, x, cnt, y, t1, t2, a[MAXN], b[MAXN];
pair <int , int > ans[MAXN];
int main()
{
	t1 = t2 = 1;
	scanf("%d %d %d %d", &n, &m, &x, &y);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; i++)
		scanf("%d", &b[i]);
	while(t1 <= n and t2 <= m)
	{
		while(a[t1] - x > b[t2] and t2 <= m)
			t2++;
		if(t2 > m or t1 > n)
			break;
		if(a[t1] - x <= b[t2] and a[t1] + y >= b[t2])
		{
			ans[++cnt].first = t1;
			ans[cnt].second = t2;
			t2++;
		}
		t1++;
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= cnt; i++)
		printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}
```
谢谢观看！

---

## 作者：QWQ_123 (赞：0)

可以考虑贪心。

先将 $a,b$ 从小到大排序。

然后若 $[a_i-x,a_i+y]$ 中有没有被选过的 $b_j$，那么就选择满足条件的最小的 $b$。

因为由于 $a$ 是从小到大，所以从 $a_i$ 到 $a_{i+1}$ 可能就覆盖不到现在最小的 $b$ 了，而在最小的 $b$ 以后的也许可以取到。如果取 $b$ 一定不劣。

例如 `x=1,y=1,a=[2 3],b=[1 2]`，那么当 $a_i=2$ 时选择了 $b_j=1$，那么当 $a_i=3$ 时就没得选了，所以选最小的 $b$ 一定不劣。

```cpp
#include<bits/stdc++.h>

using namespace std;

int n, m;
int x, y;
pair<int, int> a[100010];
pair<int, int> b[100010];

int main() {
	scanf("%d%d%d%d", &n, &m, &x, &y);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i].first), a[i].second = i;
	for (int i = 1; i <= m; ++i) scanf("%d", &b[i].first), b[i].second = i;

	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + m);
	int id = 1;

	vector<pair<int, int>> q;

	for (int i = 1; i <= n; ++i) {
		while (id <= m && a[i].first - x > b[id].first) ++id;
		if (id > m) break;
		if (a[i].first + y >= b[id].first) {
			q.push_back({a[i].second, b[id].second});
			++id;
		}
	}

	printf("%d\n", q.size());
	for (auto [u, v] : q) printf("%d %d\n", u, v);

	return 0;
}
```

---

## 作者：Ninelife_Cat (赞：0)

STL 写法。

显然对于一个 $a_i$ 可以配对多个 $b_i$ 的时候，我们优先选择最小的那个，把较大的留给后面配对。那就可以把 $a$ 数组和 $b$ 数组分别从小到大排序，通过二分查找满足条件的最小值。

这里使用了 ```multiset``` 来维护 $b$ 数组，因为 ```multiset``` 自带排序和二分查找函数，并且配对完一个 $b_i$ 之后可以直接把它 ```erase``` 掉，非常方便。

```cpp
#define fir first
#define sec second
#define ri register
#define mp make_pair
#define pb push_back
#define int long long
const int N=1e5+10;
int n,m,x,y;
struct qwq {int x,id;} a[N];
vector<pair<int,int> > v;//存放配对完的数
multiset<pair<int,int> > s;//前一维存值,后一维存下标
inline bool Cmp(qwq x,qwq y) {return x.x<y.x;}
signed main()
{
	n=read();m=read();x=read();y=read();
	for(ri int i=1;i<=n;++i)
		a[a[i].id=i].x=read();
	for(ri int i=1,t;i<=m;++i)
		t=read(),s.insert(mp(t,i));
	sort(a+1,a+n+1,Cmp);
	for(ri int i=1;i<=n;++i)
	{
		if(s.lower_bound(mp(a[i].x-x,0))==s.end()) break;//注意这里要先判断 b 中是否存在满足条件的数,否则会 RE
		pair<int,int> pos=*s.lower_bound(mp(a[i].x-x,0));
		if(pos.fir<=a[i].x+y) s.erase(s.find(pos)),v.pb(mp(i,pos.sec));//如果找到了一个 b 能和当前的 a 配对,就把它取出来
	}
	cout<<v.size()<<endl;
	for(ri int i=0;i<v.size();++i)
		cout<<v[i].fir<<" "<<v[i].sec<<endl;
	return 0;
}
```


---

## 作者：Dark_Sky (赞：0)

此题其实就是判断b数组中的数有多少在a-x到a+y的范围之内，类似于两个数组合并排序的问题，用两个下标定位即可。

上代码：
```cpp
#include <iostream>

using namespace std;
 
const int MAXN = 100001;
int a[MAXN],b[MAXN],c[MAXN],d[MAXN];
 
int main() {
	int n,m,x,y;
	int i,j,k;
	cin>>n>>m>>x>>y;
	y += x;
	for(i = 0;i < n;i++){
		cin>>a[i];
		a[i] -= x;
	}
	for(i = 0;i < m;i++){
		cin>>b[i];
	}
	k = 0;
	for(i = j = 0;i < n && j < m;){
		if(b[j] >= a[i] && b[j] <= a[i]+y){
			c[k] = ++i;
			d[k++] = ++j;
		}
		else if(b[j] < a[i]){
			j++;
		}
		else{
			i++;
		}
	}
 
	cout<<k<<endl;
	for(i = 0;i < k;i++){
		cout<<c[i]<<' '<<d[i]<<endl;
	}
	return 0;
}
```


---

