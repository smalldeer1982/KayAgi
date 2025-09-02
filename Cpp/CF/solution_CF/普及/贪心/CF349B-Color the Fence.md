# Color the Fence

## 题目描述

Igor has fallen in love with Tanya. Now Igor wants to show his feelings and write a number on the fence opposite to Tanya's house. Igor thinks that the larger the number is, the more chance to win Tanya's heart he has.

Unfortunately, Igor could only get $ v $ liters of paint. He did the math and concluded that digit $ d $ requires $ a_{d} $ liters of paint. Besides, Igor heard that Tanya doesn't like zeroes. That's why Igor won't use them in his number.

Help Igor find the maximum number he can write on the fence.

## 样例 #1

### 输入

```
5
5 4 3 2 1 2 3 4 5
```

### 输出

```
55555
```

## 样例 #2

### 输入

```
2
9 11 1 12 5 8 9 10 6
```

### 输出

```
33
```

## 样例 #3

### 输入

```
0
1 1 1 1 1 1 1 1 1
```

### 输出

```
-1
```

# 题解

## 作者：EdenSky (赞：4)

# [CF349B Color the Fence](https://www.luogu.com.cn/problem/CF349B)
- [或许更好的阅读体验](https://www.cnblogs.com/wanguan/p/17124061.html)

## 正文

**算法：贪心**

首先挑代价最小的 $a_i$，最后得到的数字越长越好。

其次可能 $v$ 还会有剩余，从高位到低位，尝试用更大的数字代替原本的数字。

其实就是贪心。

```cpp
#include<iostream>
#define int long long
#define fr(x,j) for(int i=x;i<=j;i++)
#define fs(x,j) for(int i=x;i>=j;i--)
using namespace std;
int a[10],v,m[1000005],t=1;
void is_no_ans(){
  bool no_ans=1;
  fr(1,9)if(a[i]<v)no_ans=0;
  if(no_ans)cout<<-1,exit(0);
}
signed main(){
  cin>>v; fr(1,9)cin>>a[i];
  is_no_ans();
  int mp,mx=LLONG_MAX;
  fr(1,9)if(mx>=a[i])mx=a[i],mp=i;
  while(v>=mx)m[t]=mp,t++,v-=mx;
  t--; int k=t;
  if(v)fs(t,1){
  	if(v<=0) break;
    fs(9,1)if(v+mx>=a[i]&&i>mp)
      {m[k--]=i,v=v+mx-a[i];goto pass;}
    pass:;
  }
  fs(t,1)cout<<m[i];
}
```

[完结！！](https://www.luogu.com.cn/record/102193931)

---

## 作者：lizhengdong (赞：2)

## 1.题目分析
题目意思是花油漆涂数字，让数字最大。  
求最大，明显可以贪心。

## 2.解题思路
为了数字最大，我们首先考虑数位越大，所以我们优先涂花费少的数字，使数位最大。

这样我们还会剩余油漆，显然不能浪费。  
我们从最高位开始看看能不能把数字修改变大，能就改。

所以本题总体思路就是两个贪心。
## 3.AC代码
``` cpp
#include <bits/stdc++.h>
using namespace std;
int n,i,ma,t,x,a[10],j,b[1000010];
int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;ma=2e9;
    for(i=1;i<=9;i++)cin>>a[i];
    for(i=1;i<=9;i++)
        if(a[i]<=n)break;
    if(i==10)return cout<<-1,0;//-1情况特判
    for(i=1;i<=9;i++)
        if(ma>=a[i])ma=a[i],t=i;//求最小
    x=n/ma;n=n%ma;//剩余多少油漆
    for(i=1;i<=x;i++)b[i]=t;
    for(i=1;i<=x;i++){//从最高位开始枚举
        for(j=9;j>=t;j--)//贪心
            if(n+a[t]>=a[j]){
                b[i]=j;//能修改的更大
                n=n-(a[j]-a[t]);//减少油漆
                break;
            }
        }
    for(i=1;i<=x;i++)cout<<b[i];//输出
}
```

---

## 作者：Showball (赞：2)

[或许更好的阅读体验](https://www.cnblogs.com/showball/p/17986129)
## 贪心
**题意**：
你一共有 $v$ 元，给你数字 $1 \sim 9$ 的价值。求出你能够买下的数字组成的最大数。

**思路**
首先，我们知道能够买下的数字个数越多，组成数字的位数就越多，结果自然就越大。那么，根据贪心策略，
我们可以先全买价格最便宜的数字（相同价格时，自然买更大的）。
参考代码：

```cpp
  int v;
  cin>>v;
  vector<int> a(10);
  int minn=1e6;
  for(int i=1;i<=9;i++){
    cin>>a[i];
    minn=min(minn,a[i]);
  }
  if(v<minn) return cout<<-1,void();
  int val=1;
  for(int i=1;i<=9;i++) if(a[i]==minn) val=i;
  vector<int> ans;
  for(int i=0;i<v/a[val];i++) ans.eb(val);    
  for(auto x:ans) cout<<x;         
```

顺利写出代码，发现样例没问题，然后就会喜提 `Wrong answer on test 9`，这是因为我们的钱可能并没有用完，还可以进行一些替换。
那么依然根据贪心策略，我们可以从高位到低位枚举当前数字的每一位，从 $9 \sim 1$ 查看是否可以进行替换即可。
参考代码：

```cpp
  v%=a[val];//求出剩余的钱        
  for(int i=0;i<ans.size();i++){//从高位至低位进行枚举
     for(int j=9;j>val;j--){//小于val不用进行替换
        if(v+a[val]>=a[j]){//如果可以替换，一定是最优情况，那么直接break，看下一位即可。
            ans[i]=j;
            v+=a[val]-a[j];
            break;
        }
     }
  }   
```

[完整代码](https://www.luogu.com.cn/paste/wcl0h4uw)


---

## 作者：wkjwkj (赞：2)

[更好的阅读体验](http://mywkj.github.io/2020/06/20/color-the-fence-ti-jie/)



- 贪心的性质还是比较明显的，题目中要求我们求得最大的数字，故**我们应先保证数字的长度最大，紧接着，我们要保证数字的高位越大越好**。

- 那么贪心的策略就出来了，首先找到 $a[1]$ ~$a[9]$中的最小值,用最小值去求出答案的长度，然后由高至低不断去替换答案中的每一位，最后即可得到正确答案

  代码如下

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int v;
  int a[10];
  vector<int> ans;
  int minv=1e9,id;
  int main()
  {
  	scanf("%d",&v);
  	for(int i=1;i<=9;i++){
  	scanf("%d",&a[i]);	
  	if(a[i]<=minv)minv=a[i],id=i;
  	}
  	if(minv>v){
  		puts("-1");
  		return 0;
  	}
  	while(1)
  	{
  		if(v<minv)break;
  		ans.push_back(id);
  		v-=minv;
  	}
  	for(int i=0;i<=ans.size()-1;i++)
  	{
  		int ok=1;
  		for(int j=9;j>id;j--)
  		{
  			if(a[j]-minv<=v){
  				ans[i]=j;
  				v-=a[j]-minv;
  				ok=0;
  				break;
  			}
  		} 
  		if(ok)break;
  	}
  	for(int i=0;i<=ans.size()-1;i++)printf("%d",ans[i]);
  	return 0;
  }
  ```

  

---

## 作者：Special_Tony (赞：0)

~~这种水 1700 的题解通道竟然还没关闭~~。
# 思路
首先数字判定大小的规则是先看位数，再从头到尾比较大小，所以我们首先要是位数最大。在数字和一定的情况下，要使个数最大，肯定要优先用 $a_i$ 最小的 $i$ 去填充，并把这个 $i$ 称之为 $mini$（如果有多个 $a_i$ 最小，则用 $i$ 最大的那个）。然后剩下的结余从 $ans_n\sim ans_1$，从 $9\sim mini+1$ 去枚举并贪心替换答案。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, len, a[10], ans[1000005], mini, minx = 114514, x;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 1; i < 10; ++ i) {
		cin >> a[i];
		if (a[i] <= minx)
			minx = a[i], mini = i;
	}
	len = n / minx, x = n % minx;
	if (! len) {
		cout << -1;
		return 0;
	}
	for (int i = 1; i <= len; ++ i) {
		for (int j = 9; j > mini; -- j)
			if (a[j] - minx <= x) {
				x -= a[j] - minx;
				cout << j;
				goto there;
			}
		for (int j = i; j <= len; ++ j)
			cout << mini;
		break ;
there:
		;
	}
	return 0;
}
```

---

## 作者：ZQIN_P (赞：0)

[在我的博客中阅读](https://zqin-blog.netlify.app/2023/08/25/CF349B-Color-the-Fence-%E9%A2%98%E8%A7%A3/)

[题目传送门](https://www.luogu.com.cn/problem/CF349B)

## 题目大意：
共有 $v$ 升油漆，刷上 $1 \sim 9$ 分别需要花费 $a_i$ 升油漆，问最大可以刷上的数字是多少。

## 思路：
由于要求出最大可以刷上的数字，数字越长，数值越大，所以我们可以在输入时找出花费油漆最少的数字，之后先将这些所有的数字存入到数组中，使数字的长度尽可能地长。代码如下：
```cpp
for(int i=1;i<=9;i++){
	scanf("%d",&a[i]);
	if(m_cost>=a[i]){
		m_cost=a[i];
		m_cost_num=i;
	}
}
while(v-m_cost>=0){
	w++;
	num[w]=m_cost_num;
	v-=m_cost;
}
```

但是粉刷这么多最小花费的数字后不一定可以将油漆花完，有可能这些数字还有可能增加一定的花费变为更大的数字，由于一个数字高位越大数值越大，所以我们可以从最高位开始遍历，尽可能地将位数较高的数字增大。代码如下：
```cpp
if(v>0){
	int c_w=1;
	while(v>0){
		bool b=true;
		for(int i=9;i>m_cost_num;i--){
			if(a[i]-a[m_cost_num]<=v){
				num[c_w]=i;
				v-=(a[i]-a[m_cost_num]);
				b=false;
				break;
			}
		}
		if(b) break;
		c_w++;
	}
}
```

最后将记录好的数字输出即可。

完整代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10];
int num[1000001];
int main(){
    int v,m_cost=INT_MAX,m_cost_num,w=0;
    scanf("%d",&v);
    for(int i=1;i<=9;i++){
        scanf("%d",&a[i]);
        if(m_cost>=a[i]){
            m_cost=a[i];
            m_cost_num=i;
        }
    }
    while(v-m_cost>=0){
        w++;
        num[w]=m_cost_num;
        v-=m_cost;
    }
    if(w==0){
        printf("-1");
        return 0;
    }
    if(v>0){
        int c_w=1;
        while(v>0){
            bool b=true;
            for(int i=9;i>m_cost_num;i--){
                if(a[i]-a[m_cost_num]<=v){
                    num[c_w]=i;
                    v-=(a[i]-a[m_cost_num]);
                    b=false;
                    break;
                }
            }
            if(b) break;
            c_w++;
        }
    }
    for(int i=1;i<=w;i++) printf("%d",num[i]);
    return 0;
}
```

## 总结：
本题的主要算法是贪心，还需要一点数学思维，整体难度并不算高。

---

## 作者：封禁用户 (赞：0)

## 题目描述

[Color the Fence](https://www.luogu.com.cn/problem/CF349B)

## 算法思路

### 算法：贪心

要让结果最大，肯定要让位数最多。所以我们先选择花费小的选，如果有剩余的油漆，我们就让最高位尽可能的大，让结果最大。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
struct st
{
	ll v,w;//v表示花费，w表示价值 
};
const ll N=10;
ll n=9,m,x,y;//x表示1~9中数组的最小花费，y表示这个花费下的价值 
vector<ll> ans;//ans存答案 
bool flag;//flag表示能不能写数字 
st a[N];
bool cmp(st x,st y)//按到大排序，如果花费相同，价值大的在前 
{
	if(x.v==y.v)
	{
		return x.w>y.w;
	}
	return x.v<y.v;
}
bool cmpcmp(st x,st y)//按价值从小到大排序
{
	return x.w<y.w;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化 
	cin>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].v;
		a[i].w=i;
		if(m>=a[i].v)//如果能写数字 
		{
			flag=true;
		}
	}
	if(!flag)//不能写数字 
	{
		cout<<-1<<"\n";
	}
	else//能写数字 
	{
		sort(a+1,a+n+1,cmp);//按花费从小到大排序，如果花费相同，价值大的在前
		x=a[1].v;//记录最小花费 
		y=a[1].w;//记录价值 
		while(m>=x)//选尽可能多的数 
		{
			ans.push_back(y);
			m-=x;
		}
		sort(a+1,a+n+1,cmpcmp);//按价值从小到大排序
		for(int i=0;i<=(ll)ans.size()-1;i++)
		{
			flag=true;
			for(int j=n;j>y;j--)
			{
				if(a[j].v-x<=m)//还有剩余的能改变 
				{
					ans[i]=j;//改变 
					m-=a[j].v-x;
					flag=false;
					break;
				}
			}
			if(flag)
			{
				break;
			}
		}
	}
	for(int i=0;i<=(ll)ans.size()-1;i++)//输出 
	{
		cout<<ans[i];
	}
	cout<<"\n";
    return 0;
}
```

---

## 作者：WaterSky (赞：0)

~~突然觉得自己要估值要得好过分...~~

[CF349B](https://www.luogu.com.cn/problem/CF349B)。

首先，做题的第一步是什么？读题！

 简要题面：

$1 \sim 9$ 所花费代价为 $a_i$，要求在有代价限制的条件下组成最大的数，每一个数可以使用次数不限。


然后判断算法。

因为这一道题没法直接从题目中看出使用的算法，所以要从题目描述和其他知识中仔细思考。仔细思考数的大小后得出这样的结论：

一个数的大小有关系的条件：
- 位数越多，数越大。
- 第一位越大，数越大。
- 第二位越大，数越大。
- ......

优先程度从大到小。

到这里，相信你们已经知道算法了。**贪心**+**数论**，贪心的点在于怎么选择越大的数，数论的点在于前面的条件。

其次，再思考算法的细节。

已经在上面写出了有关数的大小的条件。

那么就先使这个数的位数更多，要使这个数的位数最多的方法是什么？就是组成**全都是最小代价的数字**的数。

接下来因为可能限制还剩一些，所以我们要充分利用这些剩余的空间。我们从最高位开始，用代价允许，数更大的数来替换掉这个位数，让所有的空间充分利用。

题目简单，也不知道怎么更详细的讲，到这里就讲完了，下面是我的代码：
```
#include<bits/stdc++.h>
using namespace std;
long long v,A[1000005],n,minx=1e5,Min;
struct wbx{
	long long x,y;
}a[15];
bool cmp2(wbx x,wbx y){return x.y>y.y;}
int main()
{
	cin>>v;
	for(int i=1;i<=9;i++) 
    {
    	cin>>a[i].x,a[i].y=i;//这里我用结构体来记录。
        if(minx>a[i].x) minx=min(a[i].x,minx),Min=i;//记录最小值。
    }
	while(v>=minx) v-=minx,A[++n]=Min;//用代价最小的数组成暂时的答案。
	sort(a+1,a+10,cmp2);//为了方便用了排序，也可以不用。
	for(int i=1;i<=n;i++)
		for(int j=1;j<=9;j++)
			if(a[j].x-minx<=v){v-=(a[j].x-minx),A[i]=a[j].y;break;} //从最高位开始替换，利用空位。
	if(n==0) cout<<-1;//如果一位也没有，那么说明不可以组成任何一个数，输出-1。
	else 
    for(int i=1;i<=n;i++) cout<<A[i];//输出答案。
	return 0;
}
```

---

## 作者：WinterRain208 (赞：0)

题解 CF349B Color the Fence

### 题意

给你1到9的价值，再给你手上有的价值，求你能用手上的价值换来的数字组合在一起的最大值。

### 做法

看到这题就很简单啊，随手打个搜索就能T飞啊。

搜索思路：枚举所有可能组合出来的数字求最大值。

缺点：慢，过不了极限数据。但经过一定剪枝应该可以，本人没写。

代码：

```cpp
void dfs(ll price,ll now){
	bool f=1;
	F(i,1,9)if(price>=a[i])f=0;
	if(f){
		M=max(M,now);
		return;
	}
	F(i,1,9)if(price>=a[i])
		dfs(price-a[i],now*10+i);
}
```

接下来考虑贪心或者dp，其实贪心就可以了 。

一个数最大肯定位数最多，首先你要确定答案的位数，用 最便宜的数字的价值除你手上的价值得来。

可是这个除法会有余数，你需要使用这个余数看能不能购买更大的数字放在首位。

代码：

```cpp
for(int i=0;i<=aa.size()-1;i++){
		int f=1;
		for(int j=9;j>id;j--){
			if(a[j]-minv<=v){
				aa[i]=j;v-=a[j]-mv;f=0;
				break;
			}
		} 
		if(f)break;
	}
```


---

