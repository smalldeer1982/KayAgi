# Two Heaps

## 题目描述

Valera has $ 2·n $ cubes, each cube contains an integer from $ 10 $ to $ 99 $ . He arbitrarily chooses $ n $ cubes and puts them in the first heap. The remaining cubes form the second heap.

Valera decided to play with cubes. During the game he takes a cube from the first heap and writes down the number it has. Then he takes a cube from the second heap and write out its two digits near two digits he had written (to the right of them). In the end he obtained a single fourdigit integer — the first two digits of it is written on the cube from the first heap, and the second two digits of it is written on the second cube from the second heap.

Valera knows arithmetic very well. So, he can easily count the number of distinct fourdigit numbers he can get in the game. The other question is: how to split cubes into two heaps so that this number (the number of distinct fourdigit integers Valera can get) will be as large as possible?

## 说明/提示

In the first test case Valera can put the first cube in the first heap, and second cube — in second heap. In this case he obtain number $ 1099 $ . If he put the second cube in the first heap, and the first cube in the second heap, then he can obtain number $ 9910 $ . In both cases the maximum number of distinct integers is equal to one.

In the second test case Valera can obtain numbers $ 1313,1345,2413,2445 $ . Note, that if he put the first and the third cubes in the first heap, he can obtain only two numbers $ 1324 $ and $ 1345 $ .

## 样例 #1

### 输入

```
1
10 99
```

### 输出

```
1
2 1 
```

## 样例 #2

### 输入

```
2
13 24 13 45
```

### 输出

```
4
1 2 2 1 
```

# 题解

## 作者：Lucifer_Bartholomew (赞：3)

# 贪心
由于整个数列中总数字数一定,所以肯定平均分成两堆后可以得到的新数的组合的数量最大。

但若数列中出现相同的数,当它们被分到同一组时,因为它们与另一组的数组合后只会出现与一个该数与另一组的数组合后出现的组合相同的组合,即重复。所以为了得到尽量多的不同的数的组合,应让相同的数尽量平均分到两个堆里。
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define rr register int
#define ll long long
using namespace std;
inline int read()//读入函数不解释
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9'||ch<'0')
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        x=(x<<3)+(x<<1)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
int a[201],b[201],num[201],vis[201];//a为存读入的数组,b为存输出的数组,num计算每个数出现了多少次,vis表示这个数被拜访了几次
int main()
{
    int n=read()<<1;
    for(rr i=1;i<=n;++i)//读入,统计每个数出现了多少次
        num[a[i]=read()]++;
    int num0=0,num1=0,num2=0;//num0记有多少个相同的数,num1记第一堆里有多少个数,num2记第二堆里有多少个数
    for(rr i=1;i<=n;++i)
        if(num[a[i]]>=2)//出现了大于两次的数
        {
            if(!vis[a[i]])//没被拜访过,就放到第一堆里
            {
            	num0++;
                b[i]=vis[a[i]]=1;
            }
            else if(vis[a[i]]==1)b[i]=vis[a[i]]=2;//拜访过一次,就放到第二堆里
        }
        else if(num1>num2)//为了尽量保证两堆平均,就需要比较两堆现有的个数:如果第一堆里的数比第二堆里的数多,就放到第二堆里,否则,就放到第一堆里
        {
        	b[i]=2;
        	num2++;
        }
        else
        {
        	b[i]=1;
           	num1++;
        }
    num1+=num0;
    printf("%d\n",num1*(num2+num0));//乘法原理,可以组合出的数为两堆各自的个数相乘
    int n1=n>>1;
    for(rr i=1;i<=n;++i)//输出分配
        if(vis[a[i]]==2&&!b[i])//分配重复的数超过两个的那些数
        {
            if(num1<n1)//贪心分配,如果第一堆还不足n个,就分到第一堆,否则就分到第二堆
            {
                b[i]=1;
                num1++;
            }
            else b[i]=2;
        }
    for(rr i=1;i<=n;++i)//输出
        printf("%d ",b[i]);
    return 0;
}
```
~~我是蒟蒻~~


---

## 作者：DiDi123 (赞：1)

# 一、题意
原题面：给出 $2n$ 个两位数，现在要将其分成两堆，每堆 $n$ 个数，分好堆后每次可以从两堆分别取出一个数字组成一个四位数，问如果分可以使得组成的数字种类最多。

# 二、分析
这道题大概就是**贪心**的想法。首先我们发现如果一个数重复了很多次，应该被分到两个不同的堆里去，因为在一个堆里这两个数重复了，不会对组成四位数的种类有任何贡献。

那么，第二步就是实现将重复的数均匀分到每个堆中。我的方法就是先将所有数按照权值排序，使得相同的数都相邻，然后再交替选择。

但是会发现这样有个 bug，就是如果出现 `12 12 12 13 14 14 14 15` 这样的数据，它会把 `12 12 14 14` 分到第一堆，把剩下的分到第二堆，这样算出来答案是 $8$，而正确的答案是 $9$。

我们发现 bug 就出在 $12$ 有大于 $2$ 的奇数个，$13$ 只有 $1$ 个，$14$ 又有大于 $2$ 的奇数个。可以发现这样的三种情况连在一起会出 bug，那么就可以按照每个数出现的次数排序，把出现次数大的数排在一起，讨论发现这样就可以解决 bug 了。

# 三、代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 301
struct node {
	int pos, val;
} a[MAXN];
int n, cnt, b[MAXN], rep[MAXN], c1, c2, cnt1, cnt2, h1[MAXN], h2[MAXN];
bool cmp(node x, node y) {
	if (rep[x.val] == rep[y.val])
		return x.val < y.val;
	return rep[x.val] < rep[y.val]; //把重复次数多的数排在后面
}
int main() {
	cin >> n;
	for (int i = 1; i <= 2 * n; i++) {
		cin >> a[i].val;
		a[i].pos = i;
		rep[a[i].val]++;
	}
	sort(a + 1, a + 1 + 2 * n, cmp);
	for (int i = 1; i <= 2 * n; i++) { //交替选择
		if (c1 < c2) h1[a[i].val]++, c1++, b[a[i].pos] = 1;
		else h2[a[i].val]++, c2++, b[a[i].pos] = 2;
	}
	for (int i = 1; i <= 100; i++) {
		if (h1[i]) cnt1++;
		if (h2[i]) cnt2++;
	}
	cout << cnt1*cnt2 << endl;
	for (int i = 1; i <= 2 * n; i++)
		cout << b[i] << ' '; 
}
```


---

## 作者：1234567890sjx (赞：0)

这种题太不牛了！就这还 $1900$？

肯定是让两个集合中不同元素个数最接近最优秀。那么考虑启动贪心！把所有同样的数放到一个集合里，二元组 $(x,y)$ 表示值为 $x$ 的数所在下标的集合为 $y$。若现在访问到二元组 $(x_0,y_0)$，当前集合 $i$ 的不同元素个数为 $c_i$，则：

+ $|y|\le 1$。那么若 $c_1\le c_2$ 则让 $y_0$ 进入 $1$ 集合，否则让 $y_0$ 进入 $2$ 集合。
+ $|y|>1$。那么让 $y_0$ 进入 $1$ 集合，$y_1$ 进入 $2$ 集合，$y_i$（$2\le i<|y|$）进入 $\red 3$ 集合。

然后对于所有 $3$ 集合中的元素随便放即可。

还有不要把 $a\times 100+b$ 写成 $a\times b$，警钟撅蓝。

---

## 作者：IkunTeddy (赞：0)

# 题目分析

设 $sz_1$ 为集合一的数字种类数，$sz_2$ 为集合二的数字种类数。易得 $ans=sz_1 \times sz_2$。

我们只需让两边的种类数都尽可能多且接近即可。

贪心显然，将同种类的数字平均分配到两个集合中就行了。

有点不配蓝啊……

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200+10;
int n,N,cnt1,cnt2,sz1,sz2;
int s[maxn],disc[maxn],vis[maxn];
vector<int>t[maxn],t1,t2;
int cmp(int x,int y){return t[x].size()>t[y].size();}
int main(){
	cin>>n;
	cnt1=cnt2=n;
	for(int i=1;i<=2*n;i++){
		cin>>s[i];
		disc[++N]=s[i];
		t[s[i]].push_back(i);
	}
	sort(disc+1,disc+N+1);
	N=unique(disc+1,disc+N+1)-disc-1;
	sort(disc+1,disc+N+1,cmp);
	for(int i=1;i<=N;i++){
		int val=disc[i];
		int sz=t[val].size(),half=ceil(sz/2.0);
		if(sz&1){
			if(cnt1>cnt2){
				for(int j=0;j<half;j++){
					vis[t[val][j]]=1;
					t1.push_back(val);
					cnt1--;
				}
				for(int j=half;j<t[val].size();j++){
					vis[t[val][j]]=2;
					t2.push_back(val);
					cnt2--;
				}
			}else{
				for(int j=0;j<half;j++){
					vis[t[val][j]]=2;
					t2.push_back(val);
					cnt2--;
				}
				for(int j=half;j<t[val].size();j++){
					vis[t[val][j]]=1;
					t1.push_back(val);
					cnt1--;
				}
				
			}
		}else{
			for(int j=0;j<half;j++){
				vis[t[val][j]]=1;
				t1.push_back(val);
				cnt1--;
			}
			for(int j=half;j<t[val].size();j++){
				vis[t[val][j]]=2;
				t2.push_back(val);
				cnt2--;
			}
		}
	}
	sort(t1.begin(),t1.end());
	sz1=unique(t1.begin(),t1.end())-t1.begin();
	sort(t2.begin(),t2.end());
	sz2=unique(t2.begin(),t2.end())-t2.begin();
	cout<<sz1*sz2<<'\n';
	for(int i=1;i<=2*n;i++)cout<<vis[i]<<' ';

	return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

由于答案是两集合去重后大小的乘积，要使乘积最大，则两集合去重大小越接近。  
考虑每个集合内重复出现的元素产生的贡献也是重复的。所以有重复的添加入另一个集合，重复 $\geq 2$ 个的多于 $2$ 的部分直接不计入答案之后哪里缺扔哪里就行。  
仅出现 $1$ 次的加入元素数量最小的集合就行。

```cpp
int main() {
	int n; cin >> n;
	vector<int> a(2*n), from(2*n, 0);
	map<int, vector<int> > mp;
	for (int i = 0; i < (n << 1); ++i) {
		cin >> a[i];
		mp[a[i]].emplace_back(i);
	}
	int cnt[3]={0,0,0};
	for (auto [i,j]:mp) {
		if(j.size()>=2){//出现次数>=2次 
			from[j[0]]=1; from[j[1]]=2;
			cnt[1]++; cnt[2]++;
		}else{
			if(cnt[1]<cnt[2]){
				cnt[1]++;
				from[j[0]]=1;
			}else{
				cnt[2]++;
				from[j[0]]=2;
			}
		}
	}
	cout<<cnt[1]*cnt[2]<<'\n';
	for(int i=0;i<(n<<1);++i){
		if(from[i])cout<<from[i]<<' ';
		else cout<<(cnt[1]++<n?1:2)<<' ';	
	}
    return 0;
}
```

---

## 作者：TanX_1e18 (赞：0)

其实这题还挺简单的。

观察发现，$[a,b]$ 组合出的四位数和 $[c,b]$ 组合出的不同，当且仅当 $a\ne c$ 或 $b\ne d$。

所以组合出的四位数种类即为两个集合分别去重后的大小之积，所以只需让两个集合内的数种类尽量多即可。

用贪心很容易实现，但是细节较多，见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=209;
vector<int>v[N];
int n,in[N],top1,top2,ans1,ans2;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n*2;i++)
    {
        int x;
        cin>>x;
        v[x].push_back(i);
    }
    for(int i=0;i<=100;i++)
    {
        if(!v[i].size())
        continue;
        if(v[i].size()%2==0)
        {
            ans1++;
            ans2++;
            in[v[i][0]]=1;
            in[v[i][1]]=2;
            //两边都放
        }
        else
        {
            if(v[i].size()==1)
            {
                if(ans1>ans2)
                {
                    ans2++;
                    in[v[i][0]]=2;
                    top2++;
                }
                else
                {
                    ans1++;
                    top1++;
                    in[v[i][0]]=1;
                }
                //只放一边
            }
            else
            {
                ans1++;
                ans2++;
                in[v[i][0]]=1;
                in[v[i][1]]=2;
                //两边都放
            }
        }
    }
    for(int i=1;i<=100;i++)
    if(v[i].size()>2)
    {
        for(int j=2;j<v[i].size();j++)
        {
            if(top1<top2)
            {
                in[v[i][j]]=1;
                top1++;
            }
            else
            {
                in[v[i][j]]=2;
                top2++;
            }
        }
    }//平衡两个集合大小（一定要放到外面来）
    cout<<ans1*ans2<<'\n';
    for(int i=1;i<=n*2;i++)
    cout<<in[i]<<' ';
    return 0;
}
```


---

