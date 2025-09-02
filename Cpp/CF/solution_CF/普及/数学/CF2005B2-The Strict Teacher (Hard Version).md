# The Strict Teacher (Hard Version)

## 题目描述

**这是本题的困难版，它和本题的简单版的唯一差距是 $m$ 和 $q$ 的数据范围**。在此版本中，$m,q\le10^5$。你在解决两个版本之后才可以去提交 hack 数据。

Narek 和 Tsovak 正在热火朝天地准备这场比赛，所以他们没时间去做作业了，因此，他们决定去偷 David 的作业。

严厉的老师发现 David 的作业没了非常生气，打算狠狠地惩罚他，于是她雇佣了别的老师帮她一起抓捕 David。

现在有 $m$ 个老师正在一起追 David。幸运的是，教室非常的大，所以 David 有充足的躲藏空间。

教室可以被表示为一条一维直线，上面有 $n$ 个单元格编号从 $1$ 到 $n$，**包含边界。**

最初，David 和这 $m$ 个老师**在不同的单元格中**。然后他们将会进行若干次行动。每次行动中：
- 首先，David 可以移动到一个**相邻的**单元格中，**也可以不动。**
- 然后，每位老师也进行这样的一次移动。

行动将一直持续知道 David 被抓住，即有任何一个老师和 David 位于同一个单元格中。**所有人都看得见其它人的行动。**

你的任务是计算**在所有人按照最优方案行动的前提下，多少次行动后 David 会被抓住。**

> 按照最优方案行动，是指：
> - David 采取一种方案，使得老师抓住他所需的行动次数最大。
> - 老师之间相互配合并采用一种方案，使得他们能够用最少的行动次数抓住 David。

Narek 和 Tsovak 认为这个任务太简单了，于是他们决定给你 $q$ 次询问。

## 样例 #1

### 输入

```
2
8 1 1
6
3
10 3 3
1 4 8
2 3 10```

### 输出

```
5
1
1
2```

# 题解

## 作者：chenxi2009 (赞：2)

# 思路

简单贪心。不难发现对 David 的抓捕中，起到作用的只有离他最近的两名老师（或者墙）。分类讨论以下：

- 一面是墙，当老师把 David 逼到边上就结束；
- 两侧老师之间距离为奇数，当老师之间距离为 $2$，即 David 无法移动的时候结束；
- 两侧老师之间距离为奇数，当老师之间距离为 $1$，即 David“被夹住”的时候结束。\
$O(m+q)$ 得出答案。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m,q,b[100001],a,l,r,lef,rig,mid,ans;
int main(){
	scanf("%d",&T);
	while(T --){
		scanf("%d%d%d",&n,&m,&q);
		for(int i = 1;i <= m;i ++){
			scanf("%d",&b[i]);
		}
		sort(b + 1,b + m + 1);
		for(int i = 1;i <= q;i ++){
			scanf("%d",&a);
			l = 0,r = m;
			while(l < r){
				mid = l + r + 1 >> 1;
				if(b[mid] < a){
					l = mid;
				}
				else{
					r = mid - 1;
				}
			}
			if(!l){
				ans = b[1] - 1;
			}
			else if(l == m){
				ans = n - b[m];
			}
			else{
				lef = b[l];
				rig = b[l + 1];
				if((rig - lef) % 2 == 1){
					ans = (rig - lef - 1) / 2; 
				}
				else{
					ans = (rig - (rig + lef >> 1));
				}
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：Wide_Master (赞：1)

## 前言

第 $6$ 篇题解。

## 分析

我们可以分类讨论，明显发现，只有 David 两侧的老师或者墙有作用。同时，我们要先排序。

接下来我们开始分类讨论。

- 如果 David 的位置小于最左边的老师，那么他就可以一直往左移动，直到移动到墙，也就是说，在这种情况下，需要 $b_1-1$ 步才能抓住 David。
- 如果 David 的位置大于最右边的老师，那么他就可以一直往右移动，直到移动到墙，也就是说，在这种情况下，需要 $n-b_m$ 步才能抓住 David。
- 如果 David 的左边和右边都有老师，直到离的最近老师两面包夹，也就是说，在这种情况下，需要 $(b_r-b_l)\div2$ 步才能抓住 David。这里的 $l$ 代表离 David 最近且在左边的老师的编号，$r$ 代表离 David 最近且在右边的老师的编号。这个过程可以用二分。

## 好东西

你可以不用手写二分，因为 C++ 里面自带了两个二分函数 lower_bound 和 upper_bound。

- lower_bound 能查找第一个小于你查找数字的地址符。
- upper_bound 能查找第一个大于等于你查找的数字的地址符。

## 注意

一定要搞清楚 $n,m$ 代表者什么，不要搞混 $n,m$。~~就因为这个我调了半小时。~~

## 代码

```cpp
//By xiaozhou001
#include<bits/stdc++.h>
using namespace std;
int t,n,m,q,b,a[100007];
int main()
{
    cin>>t;
    while(t--){
        cin>>n>>m>>q;
        for(int i=1;i<=m;i++){
            cin>>a[i];
        }
        sort(a+1,a+1+m);
        for(int i=1;i<=q;i++){
            cin>>b;
            if(b<a[1]){
                cout<<a[1]-1<<endl;
            }else if(b>a[m]){
                cout<<n-a[m]<<endl;
            }else{
                int l=lower_bound(a+1,a+1+m,b)-a;
				int r=upper_bound(a+1,a+1+m,b)-a-1;
                cout<<abs(a[r]-a[l])/2<<endl;
            }
        }
    }
    return 0;
}
``````

---

## 作者：wawatime1 (赞：1)

### 题目分析
简单分析一下

 - 如果学生左边没老师，右边有老师，则向左跑到 $1$ 为最优解。
 - 如果学生左边有老师，右边没老师，则向右跑到 $n$ 为最优解。
 - 如果学生在两个老师之间，则靠得最近的老师同时两面包夹是最优解，用二分求解。

告诉你们好用的东西 lower_bound 和 upper_bound。

- lower_bound 是查找首个不小于给定值的元素的函数。
- upper_bound 是查找首个大于给定值的元素的函数。

### 代码
``` cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, m, q, a[100001], b;
int main() {
	scanf ("%d", &t);
	while(t--) {
		scanf ("%d%d%d", &n, &m, &q);
		for(int i = 1; i <= m; i++) {
			scanf ("%d", &a[i]);
		}
		sort(a + 1, a + 1 + m);
		while(q--) {
			scanf ("%d", &b);
			if(b < a[1])
				printf ("%d\n", a[1] - 1);
			else if(b > a[m]) 
				printf ("%d\n", n - a[m]);
			else {
				int l = upper_bound(a + 1, a + 1 + m, b) - a - 1;
				int r = lower_bound(a + 1, a + 1 + m, b) - a;
				printf ("%d\n", (a[l] - a[r]) / 2);
			}
		}
	}
	return 0;
}
```

---

## 作者：wujingfey (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF2005B2)

蒟蒻来水一发题解。

## 题意

在 $[1,n]$ 的数轴上有 $m$ 个老师，$q$ 次询问，每次询问会给一个学生的位置 $p$。每一回合学生先位移一个单位，然后所有老师同时再位移一个单位（可以不移动）。每个询问求最少几回合可以抓到学生。

## 题解

- 如果学生左边没老师、右边有，则向左跑到 $1$ 等死是最优解。
- 相似的如果学生右边没有老师、左边有，则向右跑到 $n$ 位置等死是最优的。
- 而如果学生位于两个老师之间，则左右靠得最近的老师同时成两面包夹之势是最优的。这时候我们用 upper_bound 和 lower_bound 可以快速求出来两侧老师的位置。

根据上述三种情况分别写代码就行了。

## CODE:
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7;
int T,n,m,q,a[N],b;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m>>q;
		for(int i=1;i<=m;i++){
			cin>>a[i];
		}
		sort(a+1,a+1+m);
		while(q--){
			cin>>b;
			if(b<a[1]) cout<<a[1]-1<<'\n';//最左边 
			else if(b>a[m]) cout<<n-a[m]<<'\n';//最右边 
			else{//在中间 
				int x1=upper_bound(a+1,a+1+m,b)-a-1;
				int x2=lower_bound(a+1,a+1+m,b)-a;
				cout<<(a[x2]-a[x1])/2<<'\n';
			}
			
		}
	}
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

一道贪心题。

无非就几种情况：

- 如果学生右边有老师，则向左跑到 $1$ 为最优解。

- 如果学生左边有老师，则向右跑到 $n$ 为最优解。

- 如果学生在两个老师之间，则靠得最近的老师同时两面包夹是最优解。

然后按照上述内容实现即可。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
const ll MAXN = 1e5 + 10;
ll T, N, M, Q, shu[MAXN];
void read () {
	cin >> N >> M >> Q;
	for (ll i = 1; i <= M; i ++) cin >> shu[i];
	sort (shu + 1, shu + 1 + M);
	while (Q --) {
		ll x; cin >> x;
		if (x < shu[1]) cout << shu[1] - 1 << endl;
		else if (x > shu[M]) cout << N - shu[M] << endl;
		else {
			ll teacher1 = upper_bound (shu + 1, shu + 1 + M, x) - shu - 1, teacher2 = lower_bound (shu + 1, shu + 1 + M, x) - shu;
			cout << (shu[teacher2] - shu[teacher1]) / 2 << endl;
		}
	}	
}
int main () {
	cin >> T;
	while (T --) read ();
	return 0;
}
```

---

## 作者：mc_xiexie (赞：0)

### 思路

别看有 $m$ 个老师，其实就只有离大卫最近的两个或一个（在大卫在所有人最右边或最左边时）。

先把老师的位置排序，如果在最左边，答案为他右边第一个老师减一。

![](https://cdn.luogu.com.cn/upload/image_hosting/ui3dugrg.png)

如果在最右边，答案为 $n$ 减他左边第一个老师减一。

![](https://cdn.luogu.com.cn/upload/image_hosting/2bt4o16q.png)

如果在中间，答案为右边的减左边的在除以二（向下取整）。

![](https://cdn.luogu.com.cn/upload/image_hosting/u7hnlphx.png)

---

## 作者：masonxiong (赞：0)

# 题目分析

首先建议大家做一下 [B1](https://www.luogu.com.cn/problem/CF2005B1) 再来看本题。

David 在所有老师左边和 David 在所有老师的右边的情况我们已经在 B1 中处理过了，那么剩下的就是 David 在老师中间的情况。

而显然，让最靠近 David 的左右共两个老师去包夹 David 是最优的。

现在此题就需要我们快速定位 David 的相对位置。将所有老师按位置升序排序后，我们可以二分查找。

---

# 题目做法

将所有老师升序排序，对于每次询问，二分查找相对位置，然后分类讨论就行。

分析一下时空复杂度：
- 时间复杂度：$O(\sum m\log m+q\log m)$。每次回答询问需要二分定位是 $O(\log m)$ 的，给老师排序是 $O(m\log m)$ 的。
- 空间复杂度：$O(m)$。我们需要存储每个老师的位置。

---

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
 
const int MAXM = 100005;
int t, n, m, q;
int a, b[MAXM], c[MAXM];
// c[i]：位于 (b[i], b[i + 1]) 中的询问的答案。
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	for (cin >> t; t--; ) {
		cin >> n >> m >> q;
		for (int i = 1; i <= m; i++)
			cin >> b[i];
		sort(b + 1, b + m + 1);
		c[0] = b[1] - 1; // 特判左边没有老师
		for (int i = 1; i < m; i++)
			c[i] = (b[i + 1] - b[i]) >> 1;
		c[m] = n - b[m]; // 特判右边没有老师
		while (q--) {
			cin >> a;
			cout << c[lower_bound(b + 1, b + m + 1, a) - 1 - b] << '\n'; // 二分回答询问
		}
	}
	return 0;
}
```

---

## 作者：wuyouawa (赞：0)

### 题目大意

有一个学生没交作业，老师召集了共 $m$ 个老师去教室抓他，教室可以表示为一条单元格从 $1$ 到 $n$ 的一维线，并给出了每个教师在哪个单元格，有 $q$ 次询问，每次询问给出学生在哪个单元格，最初所有人的位置互不相同，每一步每个人都可以留在原地或者向相邻的房间走，问最多需要几步抓住学生。
### 思路

这道题的可考虑贪心与分类讨论。容易发现只有离学生最近的两个老师才对答案有影响。如果学生在所有老师的左边，那么学生跑到最左边是最优的，也就是说，学生和老师都向左跑，答案就是学生跑到最左的步数加上离学生最近的老师追学生的步数，设学生单元格为 $c$，离学生最近的老师单元格为 $m$，则答案为 $c - 1 + m - c$，化简一下就是 $m - 1$。如果学生在所有老师的右边，那么学生跑到最右边是最优的，也就是说，学生和老师都向右跑，答案就是学生跑到最右的步数加上离学生最近的老师追学生的步数，设学生单元格为 $c$，离学生最近的老师单元格为 $m$，则答案为 $n - c + c - m$，化简一下就是 $n - m$。如果上面两种情况都不是，只需要动离学生最近的两个老师，那么离学生最近的两个老师向中间走，学生不动是最优的，因为学生动的话，无论他去哪边，那边的老师都会和另一边的老师包围住他，显然不是最优的，综上所述，设一个老师单元格为 $ma$，另一个老师单元格为 $mi$，则答案为 $\frac{ma-mi}{2}$，但是要用二分查找优化，注意有 $t$ 组数据。
### CODE


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,q,a[100005],b[100005],mi,ma,z,y;
int main(){
    cin>>t;
    while(t--)//t组数据
    {
        cin>>n>>m>>q;
        mi=1e9+1;
        ma=0;
        for(int i=1;i<=m;i++)
        {
            cin>>a[i];
            ma=max(ma,a[i]);
            mi=min(mi,a[i]);
        }
        sort(a+1,a+m+1);//因为要二分，所以先排序
        for(int i=1;i<=q;i++)
        {
             cin>>b[i];
             if(b[i]<mi)  
             {
        	    cout<<mi-1;//第一种情况
             }
             else  if(b[i]>ma)
             {
        	    cout<<n-ma;//第二种情况
             }
             else
             {
                 z=upper_bound(a+1,a+m+1,b[i])-a-1;//二分查找，查找最后一个小于b[i]的元素的下标，也就是在学生左边最靠近学生的老师的下标。
                 y=upper_bound(a+1,a+m+1,b[i])-a;//二分查找，查找第一个大于b[i]的元素，也就是在学生右边最靠近学生的老师的下标。
                 cout<<(a[y]-a[z])/2;
        	    //第三种情况，注意a[y]和a[z]才是值，y和z只是下标。
             }
             cout<<endl;
        }
       
    }
    return 0;
}
```

---

