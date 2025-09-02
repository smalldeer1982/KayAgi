# Search in Parallel

## 题目描述

Suppose you have $ n $ boxes. The $ i $ -th box contains infinitely many balls of color $ i $ . Sometimes you need to get a ball with some specific color; but you're too lazy to do it yourself.

You have bought two robots to retrieve the balls for you. Now you have to program them. In order to program the robots, you have to construct two lists $ [a_1, a_2, \dots, a_k] $ and $ [b_1, b_2, \dots, b_{n-k}] $ , where the list $ a $ represents the boxes assigned to the first robot, and the list $ b $ represents the boxes assigned to the second robot. Every integer from $ 1 $ to $ n $ must be present in exactly one of these lists.

When you request a ball with color $ x $ , the robots work as follows. Each robot looks through the boxes that were assigned to that robot, in the order they appear in the list. The first robot spends $ s_1 $ seconds analyzing the contents of a box; the second robot spends $ s_2 $ . As soon as one of the robots finds the box with balls of color $ x $ (and analyzes its contents), the search ends. The search time is the number of seconds from the beginning of the search until one of the robots finishes analyzing the contents of the $ x $ -th box. If a robot analyzes the contents of all boxes assigned to it, it stops searching.

For example, suppose $ s_1 = 2 $ , $ s_2 = 3 $ , $ a = [4, 1, 5, 3, 7] $ , $ b = [2, 6] $ . If you request a ball with color $ 3 $ , the following happens:

- initially, the first robot starts analyzing the box $ 4 $ , and the second robot starts analyzing the box $ 2 $ ;
- at the end of the $ 2 $ -nd second, the first robot finishes analyzing the box $ 4 $ . It is not the box you need, so the robot continues with the box $ 1 $ ;
- at the end of the $ 3 $ -rd second, the second robot finishes analyzing the box $ 2 $ . It is not the box you need, so the robot continues with the box $ 6 $ ;
- at the end of the $ 4 $ -th second, the first robot finishes analyzing the box $ 1 $ . It is not the box you need, so the robot continues with the box $ 5 $ ;
- at the end of the $ 6 $ -th second, the first robot finishes analyzing the box $ 5 $ . It is not the box you need, so the robot continues with the box $ 3 $ . At the same time, the second robot finishes analyzing the box $ 6 $ . It is not the box you need, and the second robot has analyzed all the boxes in its list, so that robot stops searching;
- at the end of the $ 8 $ -th second, the first robot finishes analyzing the box $ 3 $ . It is the box you need, so the search ends;
- so, the search time is $ 8 $ seconds.

You know that you are going to request a ball of color $ 1 $ $ r_1 $ times, a ball of color $ 2 $ $ r_2 $ times, and so on. You want to construct the lists $ a $ and $ b $ for the robots in such a way that the total search time over all requests is the minimum possible.

## 样例 #1

### 输入

```
3
7 3 1
8 6 4 4 4 1 7
5 1 10
1 1 1 1 1
8 1 1
4 5 6 8 1 7 3 2```

### 输出

```
2 5 6
5 1 7 2 4 3
5 4 3 5 2 1
0
4 4 2 7 5
4 6 3 1 8```

# 题解

## 作者：plank_black (赞：3)

## 思路
&emsp;&emsp;询问次数越多的球显然放在前面比放在后面更优，所以我们把小球按照询问次数从大到小排序，接下来只需要考虑放在哪一个队列中。

&emsp;&emsp;设第一个序列已经放了 $cnt_1$ 个，第二个序列放了 $cnt_2$ 个，那么再放在第一个序列的代价就是 $(cnt_1 + 1) \times s_1$，第二个序列同理，为 $(cnt_2 + 1) \times s_2$。只需判断这两个哪个小放那边就完了。

- 注意多测清空

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

const int N = 2e5 + 10;

int t, n, s1, s2;

struct node {
	int val, id;
}A[N];

vector<node> vec1, vec2;

bool cmp1(node a, node b);

int main( ) {
	cin >> t ;
	while(t--) {
		int cnt1 = 1, cnt2 = 1;
		cin >> n >> s1 >> s2;
		for(int i = 1; i <= n; i++) {
			cin >> A[i].val;
			A[i].id = i;
		}
		
		vec1.clear( );
		vec2.clear( );
		
		sort(A + 1, A + n + 1, cmp1);
		for(int i = 1; i <= n; i++) {
			if(cnt1 * s1 > cnt2 * s2) {
				vec2.push_back(A[i]);
				cnt2++;
			} else {
				vec1.push_back(A[i]);
				cnt1++;
			}
		}
		
		cout << vec1.size( ) << ' ';
		for(node x : vec1) cout << x.id << ' ';
		cout << endl;
		cout << vec2.size( ) << ' ';
		for(node x : vec2) cout << x.id << ' ';
		cout << endl;
	}
	return 0;
}

bool cmp1(node a, node b) {
	return a.val > b.val;
}
```


---

## 作者：zeekliu (赞：2)

显然询问频次越高的数应该排在前面，但排在前面显然是查询时间短，并不是在 $a$ 或者 $b$ 序列的前面。

下面是计算每一位的查询时间，然后把数值放入列表，可以边算边放。

每次 $a$ 和 $b$ 列表各向后面增加一位，比较时间，选择时间短的那个，如果两个时间一样，随便选一个插入。

最后输出方案即可，记得**输出列表内数的个数**。

感觉写的有些抽象，下面直接代码：

```cpp
//CF1814C 23.04.07
#include <bits/stdc++.h>
using namespace std;

struct R
{
    int nu,id;
}r[200010];

int _,n,s1,s2;
int a[200010],b[200010];

bool cmp(R x,R y)
{
    return x.nu>y.nu;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>_;
    while (_--)
    {
        cin>>n>>s1>>s2;
        for (int i=1;i<=n;i++) cin>>r[i].nu,r[i].id=i;
        sort(r+1,r+n+1,cmp);
        a[0]=0,b[0]=0;
        int c1=0,c2=0,t=1;
        for (;t<=n;t++)
        {
            int p=0;
            if (c1+s1<=c2+s2) c1+=s1,p=1;
            else c2+=s2,p=2;
            if (p==1)
            {
                a[0]++,a[a[0]]=r[t].id;
            }
            else if (p==2)
            {
                b[0]++,b[b[0]]=r[t].id;
            }
        }
        cout<<a[0]<<" ";
        for (int i=1;i<=a[0];i++) cout<<a[i]<<" ";
        cout<<endl<<b[0]<<" ";
        for (int i=1;i<=b[0];i++) cout<<b[i]<<" ";
        cout<<endl;
    }
    exit(0);
}
```

---

## 作者：Sun_pirf (赞：0)

# 思路

容易发现：

1. 询问次数越多的放在前面球明显比放在后面更优。
2. 设 $x_{1,2}$ 分别为两个序列已经放的球，所以两个序列在放时，代价都为 $(x_i+1) \times t_i$。

所以应当先排一个序（按询问次数），放的时候只需要分别算出两个序列分别代价，再比较一下就可以完成，但没有用数组记录的，一定记得**多测要清空**。

代码内有部分注释。

> P.S. 有 SPJ，发现与样例不同时，手推一下。

# 代码

```cpp
#include<bits/stdc++.h>
#define N 200005
using namespace std;
struct node{
	int tim;//次数
	int id;//编号
}ball[N];
int T;
int n,s1,s2;
int ans1[N],cnt1;//序列1
int ans2[N],cnt2;//序列2
bool cmp(node x,node y){
	if(x.tim!=y.tim)
		return x.tim>y.tim;
	if(x.id!=y.id)
		return x.id>y.id;
} //排序用
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>T;
	for(int iii=1;iii<=T;iii++){
		cin>>n>>s1>>s2;
		for(int i=1;i<=n;i++){
			cin>>ball[i].tim;
			ball[i].id=i;
		}
		sort(ball+1,ball+n+1,cmp);//排序
		cnt1=cnt2=1;
		for (int i=1;i<=n;i++){
			if (cnt1*s1<cnt 2*s2){ //分入两个序列
				ans1[cnt1]=ball[i].id;
				cnt1++;
			}
			else{
				ans2[cnt2]=ball[i].id;
				cnt2++;
			}
		}
		cout<<cnt1-1<<" ";
		for(int i=1;i<cnt1;i++){
			cout<<ans1[i]<<" ";
		}
		cout<<"\n"<<cnt2-1<<" ";
		for(int i=1;i<cnt2;i++){
			cout<<ans2[i]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
挺像某些排队接水的问题的。

首先肯定让询问次数越多的小球排在越前面，所以要从大到小排序再枚举。然后看看 $a$ 和 $b$ 中哪个排队时间短就去那一堆。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, s1, s2, m1, m2, ans1[200005], ans2[200005];
pii a[200005];
int main () {
	ios::sync_with_stdio (0);	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> s1 >> s2;
		for (int i = 1; i <= n; ++ i)
			cin >> a[i].first, a[i].second = i;
		sort (a + 1, a + n + 1, greater <pii> ());
		m1 = m2 = 1;
		for (int i = 1; i <= n; ++ i)
			if (m1 * s1 < m2 * s2)
				ans1[m1] = a[i].second, ++ m1;
			else
				ans2[m2] = a[i].second, ++ m2;
		cout << m1 - 1 << ' ';
		for (int i = 1; i < m1; ++ i)
			cout << ans1[i] << ' ';
		cout << '\n' << m2 - 1 << ' ';
		for (int i = 1; i < m2; ++ i)
			cout << ans2[i] << ' ';
		cout << '\n';
	}
	return 0;
}
```

---

