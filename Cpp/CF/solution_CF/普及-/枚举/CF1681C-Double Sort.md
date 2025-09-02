# Double Sort

## 题目描述

你被给予了两个数组 $a$ 和 $b$，他们都有 $n$ 个数子。

在一步中，你可以选择两个数 $i$ 和 $j(1 \leq i,j \leq n; i \ne j)$ 并交换 $a_i$、$a_j$ 和 $b_i$、$b_j$。你必须交换这两个数组。

你最多可以执行 $10^4$ 次交换操作（可能为零次）。你能使两个数组都排序成非递减顺序么？如果可以，请打印所有使两个数组都成非递减顺序的移动序列。

## 样例 #1

### 输入

```
3
2
1 2
1 2
2
2 1
1 2
4
2 3 1 2
2 3 2 3```

### 输出

```
0
-1
3
3 1
3 2
4 3```

# 题解

## 作者：Withershine (赞：9)

~~一道普及-我写了两个半小时~~

[题面](https://www.luogu.com.cn/problem/CF1681C)

需要注意的是，每次交换需要将 a 和 b 两个数组同时交换，因此便可以想到唯一可行情况： a ， b 序列数字间的大小关系必须一致。

举个例子

2 4 6 21 3 1 3
 
1 7 9 70 6 1 2

在上面的例子中，两个序列中任意 $i$ 和 $j$ 满足 $a_i \le a_j$ 时 $b_i \le b_j$ ，或者 $a_i \ge a_j$ 时 $b_i \ge b_j$ ，此时上下同时交换这两个数的位置，前面的结论仍然成立。因此，便可以得到一个判断是否有解的部分代码。

```c
flag = 1;
fr(i , 2 , n)
{
	if((a[i] <= a[i - 1] && b[i] <= b[i - 1]) || (a[i] >= a[i - 1] && b[i] >= b[i - 1]))
	{
		continue;
	}
	flag = 0;
}
if(!flag)
{
	printf("-1\n");
	continue;
}
```

对于同时交换两个数组的操作，考虑冒泡排序，由于 $2 \le n \le 100$ ，因此冒泡排序可以放心食用。

在每次交换时，判断只要 a 数组或者 b 数组满足交换条件，便可以同时交换，同时用一个 `ans` 数组记录交换次数及步骤。

由于是只要 a 数组或者 b 数组满足交换条件便同时交换，需要再遍历此时的两个数组是否依旧符合题意（~~不然就WA#2~~）。

还需要注意一点，输出的 `k` 必须不能超过 $10^4$ ，否则就直接输出 `-1` 。

这是我奇怪的代码。

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<stack>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ld double
#define ll long long
#define maxx 200005
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
#pragma comment(linker , "/stack : 200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = gchar();
    while(ch < '0' || ch > '9')
	{
        if(ch == '-')
        {
        	f = -1;
		}
        ch = gchar();
    }
    while(ch >= '0' && ch <= '9')
	{
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = gchar();
    }
    return x * f;
}
ll T , n , a[maxx] , b[maxx];
ll flag;
struct node
{
	ll i , j;
}ans[maxx];
signed main()
{
	T = read();
	while(T--)
	{
		n = read();
		fr(i , 1 , n)
		{
			a[i] = read();
		}
		fr(i , 1 , n)
		{
			b[i] = read();
		}
		flag = 1;
		fr(i , 2 , n)
		{
			if((a[i] <= a[i - 1] && b[i] <= b[i - 1]) || (a[i] >= a[i - 1] && b[i] >= b[i - 1]))
			{
				continue;
			}
			flag = 0;
		}
		if(!flag)
		{
			printf("-1\n");
			continue;
		}
		ll k = 0;
		fr(i , 1 , n)
		{
			fr(j , i + 1 , n)
			{
				if(a[i] > a[j] || b[i] > b[j])
				{
					swap(a[i] , a[j]);
					swap(b[i] , b[j]);
					ans[++k].i = i;
					ans[k].j = j;
				}
			}
		}
		flag = 1;
		fr(i , 2 , n)
		{
			if(b[i] < b[i - 1] || a[i] < a[i - 1])
			{
				flag = 0;
				break;
			}
		}
		if(flag && k <= 10000)
		{
			printf("%lld\n" , k);
			fr(i , 1 , k)
			{
				printf("%lld %lld\n" , ans[i].i , ans[i].j);
			}
		}
		else
		{
			printf("-1\n");
		}
	}
    return 0;
}
```


---

## 作者：YCSluogu (赞：4)

# CF1681C题解

[可爱的题面传送门](https://www.luogu.com.cn/problem/CF1681C)

题意很好理解，就是让我们在执行若干次交换操作后，使得数组 $a$ 与数组 $b$ 变成非减序列。

若我们丢开数组 $b$ 不谈，只考虑数组 $a$，同时题目不需要我们考虑次数最小化，利用简单的冒泡排序就可以实现交换的同时记录下交换步骤。

此时考虑数组 $b$，我们就会发现这其实是一个双关键字排序。在冒泡排序过程中，若 $a_{i}=a_{j}$，就利用 $b_{i}$ 与 $b_{j}$ 进行排序。

于是进行比较并且交换部分的代码就很容易写出来了：

``` cpp
if (a[i] == a[j] ? b[i] < b[j] : a[i] < a[j]) {
  // ...
}
```

但是当我们排序之后可能会面临 $b$ 数组无序，此时遍历一遍判断即可。

我感觉我的代码写的算短的：

``` cpp
#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 1e6;

int n;
int a[kMaxN], b[kMaxN];
int cnt;
int l[kMaxN], r[kMaxN];

void solve() {
  cnt = 0;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (a[i] == a[j] ? b[i] < b[j] : a[i] < a[j]) {
        swap(a[i], a[j]);
        swap(b[i], b[j]);
        l[++cnt] = i, r[cnt] = j;
      }
    }
  }
  for (int i = 2; i <= n; i++) {
    if (b[i] < b[i - 1]) {
      printf("-1\n");
      return;
    }
  }
  printf("%d\n", cnt);
  for (int i = 1; i <= cnt; i++) {
    printf("%d %d\n", l[i], r[i]);
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
```

吐槽一句：这道题如果用 `cin` `cout` 最后一个点会很慢。


---

## 作者：EthanOI (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1681C)
### 前言
同时写了翻译和题解，不知道哪个先过，~~还是都没过~~
### 思路
本题还是较为常规的。在输入之后，我们将两个数组直接用 sort 进行排序，然后判断是否存在降序，如果有，输出 $-1$ ，否则进行冒泡排序，统计每一次操作时的 $i$ 与 $j$ （在代码中为 $ans$ 数组）最后输出即可。
### 代码
尽管思路很清晰，代码还是有点长（我指在橙题中），打代码时需要小心。

[$\mathcal{AC} \text{ } \mathcal{CODE}$](https://www.luogu.com.cn/record/77296332)（c++）：
```cpp
#include <bits/stdc++.h> //万能投文件 
using namespace std;
struct p{int a, b, pos;}a[110]; //创建结构体，使代码更加好写  
int T, n, cnt, ans[100010][2]; //T组数，n每一组元素个数，cnt步数，ans统计方法  
bool t = true;
/*结构体排序函数，在后面用 sort 排序时用到*/
bool cmp(p a, p b)
{
	if (a.a == b.a) return a.b < b.b;
	return a.a < b.a;
}
int main()
{
	cin >> T;
	while (T--)
	{
		cnt = 0; //记录答案的操作次数，初始化为0  
		cin >> n;
		for (int i = 1; i <= n; i++)
			a[i].pos = i;
		for (int i = 1; i <= n; i++)
			cin >> a[i].a;
		for (int i = 1; i <= n; i++)
			cin >> a[i].b;
		sort(a + 1, a + n + 1, cmp);//排序 
		t = true;
		/*检查是否存在降序部分，如果有，则 t 变为 false ，并退出循环*/
		for (int i = 1; i < n; i++)
			if (a[i].a > a[i+1].a || a[i].b > a[i + 1].b)
			{
				t = false;
				break;
			}
		/*若t为false，说明本次操作不可以做到，输出-1跳过本次循环*/
		if (!t)
		{
			cout << -1 << endl;
			continue;
		}
		/*好久没写过的冒泡排序*/
		for (int i = 1; i < n; i++)
			for (int j = i + 1; j <= n; j++)
				if (a[i].pos > a[j].pos)//前面的位置数据比后面的大
				{
					swap(a[i], a[j]); //交换  
					ans[++cnt][0] = i, ans[cnt][1] = j; //记录操作  
				}
		cout << cnt << endl; //输出操作次数 
		for (int i = cnt; i >= 1; i--) //反向输出答案 
			cout << ans[i][0] << " " << ans[i][1] << endl;
	}
	return 0;
}
```
### 结语
代码最好不要直接抄，建议看一遍后自己写，当然，想棕名的人我也拦不住

---

## 作者：zjzx_wcj (赞：1)

# 题解：CF1681C Double Sort

[题目传送门](/problem/CF1681C)

## 思路

~~这是一道大水题~~。

首先我们先找无解条件：$a_i$ 和 $b_i$ 大小的顺序不一样！！！比如样例里：
```
2
1 2
2 1
```
接着，你就会发现，不管你怎么搞，都不可能搞成有序的。

所以，就可以写出代码（我用了选择排序和函数）：

```cpp
reg (i,1,n-1)
	reg (j,i+1,n)
		if ((a[i]>=a[j]&&b[i]>=b[j])||(a[i]<=a[j]&&b[i]<=b[j])||(a[i]==a[j]&&b[i]==b[j])) ;
			else {writeln (-1);return ;}
```
OK，第一个输出 $-1$ 的条件有了，但下面还有一个要输出 $-1$ 的点（划下去看就行了）。

接着，开始解决步骤的问题。由于题目里有：如果有多个答案，则打印其中任何一个。你不必尽量减少移动的次数。所以，可以使用刚刚用过的选择排序来解决。**注意：条件之中 $a_i$ 和 $b_i$ 之间一个可以相等！！！**

接下来可以说第二个输出 $-1$ 的条件了（**这也是个大坑点！！！**），**交换次数 $> 10^4$ 也要输出 $-1$**！！！

## 代码参考

为了防止 ctj，代码只给出重要部分：

```cpp
inline void work ()
{
	n=read ();
	reg (i,1,n) a[i]=read ();
	reg (i,1,n) b[i]=read ();
	reg (i,1,n-1)
		reg (j,i+1,n)
			if ((a[i]>=a[j]&&b[i]>=b[j])||(a[i]<=a[j]&&b[i]<=b[j])||(a[i]==a[j]&&b[i]==b[j])) ;
				else {writeln (-1);return ;}
	vector<pair<int,int> > f;
	f.clear ();
	reg (i,1,n)
		reg (j,i+1,n)
			if (a[i]>=a[j]&&b[i]>=b[j])
			{
				swap (a[i],a[j]);
				swap (b[i],b[j]);
				f.push_back ({i,j});
				if (f.size ()>10000) {writeln (-1);return ;}
			}
	writeln (f.size ());
	if (f.size ()==0) return ;
	reg (i,0,f.size ()-1) writesp (f[i].first),writeln (f[i].second);
	return ;
}
```

---

## 作者：happy_dengziyue (赞：1)

### 1 视频题解

![](bilibili:BV1T541197NA)

### 2 思路

首先，我们依次将 $a$ 数组排序。

具体操作方法是，看到一个不符合要求的数，就往后面找一个符合要求的过来。

可以发现，在这个环节最多花费 $n-1$ 次操作。

然后，在保证 $a$ 数组不乱的情况下，对 $b$ 数组也同样操作。也最多是 $n-1$ 次操作。

所以最多 $2n-2$ 次操作，在极限数据下只有 $198$，远远小于 $10000$ 的要求。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 100
int t;
int n;
int a[max_n+2];
int aa[max_n+2];
int b[max_n+2];
int bb[max_n+2];
int k;
int l[max_n*max_n+2];
int r[max_n*max_n+2];
bool ans;
inline void sw(int &a,int &b){a^=b^=a^=b;}
inline void upd(int u,int v){
	sw(a[u],a[v]);
	sw(b[u],b[v]);
	++k;
	l[k]=u;
	r[k]=v;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1681C_1.in","r",stdin);
	freopen("CF1681C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
			aa[i]=a[i];
		}
		a[n+1]=-1;
		for(int i=1;i<=n;++i){
			scanf("%d",b+i);
			bb[i]=b[i];
		}
		sort(aa+1,aa+n+1);
		sort(bb+1,bb+n+1);
		k=0;
		for(int i=1;i<=n;++i){
			if(a[i]==aa[i])continue;
			for(int j=i+1;j<=n;++j){
				if(a[j]==aa[i]){
					upd(i,j);
					break;
				}
			}
		}
		ans=true;
		for(int x=1,y=1;x<=n;x=y+1){
			y=x;
			while(a[y]==a[y+1])++y;
			for(int i=x,fl;i<=y;++i){
				if(b[i]==bb[i])continue;
				fl=false;
				for(int j=i+1;j<=y;++j){
					if(b[j]==bb[i]){
						upd(i,j);
						fl=true;
						break;
					}
				}
				if(!fl){
					ans=false;
					break;
				}
			}
			if(!ans)break;
		}
		if(!ans)printf("-1\n");
		else{
			printf("%d\n",k);
			for(int i=1;i<=k;++i)printf("%d %d\n",l[i],r[i]);
		}
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/76377451)

By **dengziyue**

---

## 作者：Cappuccino_mjj (赞：1)

这是蒟蒻我第一次写题解，球球管理员通过吧。

---

## [题目传送门](https://www.luogu.com.cn/problem/CF1681C)

这道题目的意思就是给我们两个数组 $a$ 和 $b$，然后进行排序。但是两个数组下标相同的数字（即 $a_i$，$a_j$ 交换时 $b_i$，$b_j$ 也要交换）要同时交换。问题是是否经过若干次排序之后两个数组都是非递减顺序。

思路：
1. 首先我们发现 $n$ 的最大值仅有 $100$，所以可以考虑使用冒泡排序。
2. 接着我们先备份这两个数组（后面用），然后排序原来的数组，并用一个变量 $ans$ 来记录一共交换了多少次。
3. 排序完原来的数组后我们判断两个数组是否都是非递减顺序，如果不是，证明不行，则输出 $-1$；如果是，输出 $ans$，然后用我们备份的数组再进行一次冒泡排序，交换时输出 $i$ 和 $j$ 即可。

---

代码：
```cpp
#include<iostream>
using namespace std;
int a[105],b[105],aa[105],bb[105];
int t,n;
int main()
{
	cin>>t;
	while(t--)
	{
		int ans=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i],aa[i]=a[i];//备份a数组
		for(int i=1;i<=n;i++)
			cin>>b[i],bb[i]=b[i];//备份b数组
		for(int i=1;i<n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				if(a[j]<a[i]||b[j]<b[i])
				{
					swap(a[j],a[i]),swap(b[j],b[i]);
					ans++;//冒泡排序，同时记录交换次数
				}
			}
		}
		bool f=0;
		for(int i=1;i<n;i++)
		{
			if(a[i]>a[i+1]||b[i]>b[i+1])
			{
				f=1;
				break;
			}//判断是否为非递减数列
		}
		if(f)
		{
			cout<<-1<<endl;
			continue;
		}
		cout<<ans<<endl;
		if(!ans)continue;
		for(int i=1;i<n;i++)
		{
			for(int j=i+1;j<=n;j++)
			{
				if(aa[i]>aa[j]||bb[i]>bb[j])
				{
					swap(aa[i],aa[j]);
					swap(bb[i],bb[j]);
					cout<<i<<" "<<j<<endl;
				}//再来一次冒泡，并输出过程
			}
		}
	}
	return 0;
}
```

---

完美撒花~

---

## 作者：zhoujunchen (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1681C)&&[CF传送门](https://codeforces.com/problemset/problem/1681/C)
 
做题思路
---
- 读入数据。

- 将读入的数据进行排序。

- 如果排好的数组是递减顺序或 $k >10^4$ 输出 -1。

- 如果可以排序，使用冒泡排序记录每次操作，并输出操作次数和具体的操作步骤。

code:  
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    int a,b,pos;//a和b分别表示两个数组的元素，pos表示原始位置
};
bool cmp(node x,node y) {
    if(x.a==y.a)return x.b<y.b;
    return x.a<y.a;
}
int main(){
    ios::sync_with_stdio(0);//最后一个点cin cout有亿点慢
    cin.tie(0);
    cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        vector<node> arr(n);
        for(int i=0;i<n;i++)arr[i].pos=i+1;//每个元素的初始位置
        for(int i=0;i<n;i++)cin>>arr[i].a;
        for(int i=0;i<n;i++)cin>>arr[i].b;
        sort(arr.begin(),arr.end(),cmp);
        bool canSort=true;
        //检查是否已经是非递减顺序
        for(int i=0;i<n-1;i++)//如果递减
            if(arr[i].a>arr[i+1].a||arr[i].b>arr[i+1].b){
                canSort=false;//排不了
                break;
            }
        if(!canSort){//排不了输出-1
            cout<<-1<<"\n";
            continue;
        }
        //如果可以排序，使用冒泡排序记录每一步操作
        vector<pair<int,int>> ans;
        for(int i=0;i<n;i++) {
            for(int j=i+1;j<n;j++){
                if(arr[i].pos>arr[j].pos){
                    swap(arr[i],arr[j]);
                    ans.push_back({arr[i].pos,arr[j].pos});
                }
            }
        }
        //输出操作次数和每次操作的具体步骤
        cout<<ans.size()<<"\n";
        for(auto op:ans)cout<<op.second<<" "<< op.first<<"\n";
    }
    return 0;
}
```

---

## 作者：ny_Dacong (赞：0)

# 思路

我们要让两个数组都以非递减顺序排序，也就是说，对于每个 $i,j$，我们要让 $a_i \le a_j$ 并且 $b_i \le b_j$。所以，未排序时， $a_i$ 与 $a_j$ 的大小关系和 $b_i$ 与 $b_j$ 的大小关系是一样的。

那么无解的情况就出来了。想明白这一点后，接下来的排序就简单了。

因为我们只关注数字之间的大小关系，而我们已经确认对于每个 $i,j$， $a_i$ 与 $a_j$ 的大小关系和 $b_i$ 与 $b_j$ 的大小关系是一样的。所以我们就可以只考虑其中一个数组，另外一个自然就排好了。

具体实现时，排序可以用冒泡；无解不需要单独判断，可以排完之后检查另一个数组是否有序；操作可以用队列记录。

# AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n = 0,ans = 0;
struct nums{
    int a,b;
}num[105];
bool cmp(nums x,nums y){
    if(x.a == y.a){
        return x.b > y.b;
    }
    return x.a > y.a;
}
queue<pair<int,int>> que;
int main(){
    scanf("%d",&t);
    while(t--){
        ans = 0;
        while(que.size()){
            que.pop();
        }
        for(int i = 1; i <= n; i++){
            num[i] = {0,0};
        }
        scanf("%d",&n);
        for(int i = 1; i <= n; i++){
            scanf("%d",&num[i].a);
        }
        for(int i = 1; i <= n; i++){
            scanf("%d",&num[i].b);
        }
        bool flag = 1;
        for(int i = n; i >= 1; i--){
            flag = 1;
            for(int j = 1; j < i; j++){
                if(cmp(num[j],num[j+1])){
                    flag = 0;
                    swap(num[j],num[j+1]);
                    que.push({j+1,j});
                    ans++;
                }
            }
            if(flag){
                break;
            }
        }
        if(ans > 10000){
            printf("-1\n");
            continue;
        }
        flag = 1;
        for(int i = 2; i <= n; i++){
            if(num[i].b < num[i-1].b){
                flag = 0;
                break;
            }
        }
        if(flag){
            printf("%d\n",ans);
            while(que.size()){
                printf("%d %d\n",que.front().first,que.front().second);
                que.pop();
            }
        }else{
            printf("-1\n");
        }
    }
    return 0;
}
```

---

## 作者：Michael1234 (赞：0)

- 本题可以使用**模拟**的思路：

- 首先，先考虑这两个数组是否无解，如果他们出现了其中任意两组数的**大小关系**不同，则无解，例如：

~~~
1 2 3 2 1
3 2 1 2 3
~~~
- 很明显，这样无法求解。

- 判断完以后，我们进行**冒泡排序**，每进行一次值的互换，进行一次记录。

- 接下来，判断两个序列是否已经被排好，并且步数不超过 $10^4$。

- 如果是，输出记录的过程。否则，无解。

## CODE

~~~cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=105;
int t,n,a[N],b[N];
bool flag;
vector<pair<int,int> >v;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>t;
	while(t--)
	{
		flag=true;
		v.clear();
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=1;i<=n;i++)
		{
			cin>>b[i];
		}
		for(int i=2;i<=n;i++)
		{
			if(a[i]<=a[i-1]&&b[i]<=b[i-1])//大小关系是否相同
			{
				continue;
			}
			else if(a[i]>=a[i-1]&&b[i]>=b[i-1])
			{
				continue;
			}
			else//不同
			{
				flag=false;
			}
		}
		if(!flag)//无解
		{
			cout<<"-1\n";
			continue;
		}
		for(int i=1;i<=n;i++)//冒泡排序
		{
			for(int j=i+1;j<=n;j++)
			{
				if(a[i]>a[j]||b[i]>b[j])//需要交换
				{
					swap(a[i],a[j]);
					swap(b[i],b[j]);//交换
					v.push_back({i,j});//进行记录
				}
			}
		}
		for(int i=1;i<n;i++)
		{
			if(a[i]>a[i+1]||b[i]>b[i+1])//是否排好
			{
				flag=false;//没排好
				break;
			}
		}
		if(v.size()<=10000&&flag)//拍好了并且步数不超过10000
		{
			cout<<v.size()<<"\n";
			for(auto i=v.begin();i!=v.end();i++)
			{
				cout<<i->first<<" "<<i->second<<"\n";
			}//进行输出
		}
		else
		{
			cout<<"-1\n";//否则无解
		}
	}
	return 0;
}
~~~

---

## 作者：hdkghc (赞：0)

题目传送门：[CF1681C](https://www.luogu.com.cn/problem/CF1681C)。

## 题意简化

给定两数列 $a$ 和 $b$，通过少于 $10^4$ 次操作使两数列都非递减。

## 思路

由于题目中并没有要求操作次数最少，考虑使用冒泡排序。在冒泡时记录即可。  
不过，因为是双关键字排序，排好时 $b$ 数列并不一定都非递减（对于以 $a$ 数列的元素作为第一关键字来说）。所以排好序还得遍历一遍 $b$ 数列。如果 $b$ 数列不满足非递减，即 $\exists 1 \le i < n, b_i > b_{i + 1}$，则说明无解，否则就输出方案。

## 代码

```cpp
/*********************************************************************
    程序名: 
    版权: Copyleft (c) 2023~9999 hdkghc
    作者: hdkghc
    日期: 2023-10-09 20:39
    说明: This is a codeforces program.
*********************************************************************/
#include <bits/stdc++.h>
#define f1() for(int i = 1; i <= n; i++)
#define f2(i) for(int i = 1; i <= n; i++)
#define f3(i, from, to) for(int i = from; (from <= to) ? (i <= to) : (i >= to); i += (from <= to ? 1 : -1))
#define f4(i, from, to, step) for(int i = from; (from <= to) ? (i <= to) : (i >= to); i += (from <= to ? 1 : -1) * step)
#define f5(i, from, to, comp, cng) for(int i = from; comp(i, to); cng(i))
#define leq(tp) [](tp a, tp b) { return a <= b; }
#define geq(tp) [](tp a, tp b) { return a >= b; }
#define neq(tp) [](tp a, tp b) { return a != b; }
#define add1(tp) [](tp &a) { a++; }
using namespace std;
int t;

int _main()
{
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		int a[n + 1], b[n + 1];
		f1()
		{
			cin >> a[i];
		}
		f1()
		{
			cin >> b[i];
		}
		vector<pair<int, int>> step;
		step.clear();
		f1()
		{
			f5(j, 1, i - 1, leq(int), add1(int))
			{
				if(a[i] == a[j] ? b[i] < b[j] : a[i] < a[j]) // 双关键字排序
				{
					swap(a[i], a[j]);
					swap(b[i], b[j]);
					step.push_back(make_pair(i, j)); // 记录
				}
			}
		}
		f3(i, 2, n)
		{
			if(b[i] < b[i - 1]) // 无解情况
			{
				cout << -1 << endl;
				goto end;
			}
		}
		cout << step.size() << endl;
		for(auto u : step) // 输出答案
		{
			cout << u.first << ' ' << u.second << endl;
		}
		end: continue;
	}
	return 0;
}
#ifdef _LOCAL_TEST
int main()
{
	string fn = (string)__FILE__ + (string)".out.txt";
	system(((string)"type nul > \"" + fn + (string)"\"").data());
	ofstream fout(fn);
	streambuf *outbuf = cout.rdbuf();
	cout.rdbuf(fout.rdbuf());
	clock_t st = clock();
	_main();
	clock_t tim = clock() - st;
	fout.close();
	cout.rdbuf(outbuf);
	system(("start notepad " + fn).data());
	cout << "Execute Time: " << (static_cast<double>(tim) / 1000.0) << endl;
	system("pause > nul");
	return 0;
}
#elif defined(INTERACTIVE)
int main()
{
    _main();
    system("pause > nul");
    return 0;
}
#else
int main()
{
	_main();
	return 0;
}

#endif

---

## 作者：cyrxdzj (赞：0)

### 一、思路

显然，操作次数有 $10^4$ 那么多，在 $n\le100$ 时完全足够，因为通过将一个长度为 $n$ 的数组进行交换而得到任意排序，最多只需要操作 $n^2$ 次甚至更少。

这道题可以使用结构体。这个结构体有 $3$ 个数据：`a` 数组在此位置的数值，`b` 数组在此位置的数值，以及此位置具体是在哪个位置。

然后，对结构体数组进行排序，规则如下：

1. 按照 `a` 数组数据升序排序；

2. 如果 `a` 数组数据一样，则按 `b` 数组数据升序排序。

然后，检查此时的两个数组是否存在降序部分。如果有，判无解。

别忘了之前的位置数据也在随着排序而更改顺序。此时，我们通过手写一个冒泡排序，将位置数据再次排序，以得到交换操作的具体内容。

最后反向输出即可。

### 二、代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int a,b,index;
}a[105];//结构体数组。
int t;
int n;
int cnt;
int ans[100005][2];
bool cmp(node a,node b)//排序函数。其实没必要排位置数据。
{
	if(a.a==b.a)
	{
		if(a.b==b.b)
		{
			return a.index<b.index;//没必要的内容。
		}
		return a.b<b.b;
	}
	return a.a<b.a;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=1;i<=n;i++)//输入。
		{
			scanf("%d",&a[i].a);
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i].b);
			a[i].index=i;//记录位置数据。
		}
		sort(a+1,a+1+n,cmp);//排序。
		bool flag=true;
		for(int i=1;i<n;i++)//检查是否存在降序部分。
		{
			if(a[i].a>a[i+1].a||a[i].b>a[i+1].b)
			{
				flag=false;
				break;
			}
		}
		if(!flag)
		{
			printf("-1\n");
			continue;
		}
		cnt=0;//答案的操作次数。
		for(int i=1;i<n;i++)//手写冒泡。
		{
			for(int j=i+1;j<=n;j++)
			{
				if(a[i].index>a[j].index)//前面的位置数据比后面的大
				{
					node c=a[i];//交换
					a[i]=a[j];
					a[j]=c;
					ans[++cnt][0]=i;//记录答案
					ans[cnt][1]=j;
				}
			}
		}
		printf("%d\n",cnt);//输出操作次数
		for(int i=cnt;i>=1;i--)//反向输出答案
		{
			printf("%d %d\n",ans[i][0],ans[i][1]);
		}
	}
	return 0;
}

```


---

