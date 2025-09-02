# [GCJ 2017 #1C] Ample Syrup

## 题目描述

无限煎饼屋的厨房刚刚收到了一份包含 $K$ 张煎饼的订单！厨师目前有 $N$ 张煎饼可用，其中 $N \geq K$。每张煎饼都是一个圆柱体，不同的煎饼可能有不同的半径和高度。

作为副厨师，你需要从这 $N$ 张煎饼中选择 $K$ 张，丢弃其余的煎饼，并将这 $K$ 张煎饼按如下方式叠放在盘子上。首先，取出半径最大的煎饼，将其一面圆形朝下放在盘子上。（如果有多张煎饼半径相同，可以任选其中一张。）然后，取剩下的半径次大的煎饼，叠放在第一张煎饼上，以此类推，直到所有 $K$ 张煎饼都叠好，并且所有圆形面的中心都在一条垂直于盘子的直线上，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/57lkgshp.png)

你知道，食客们除了喜欢煎饼外，还同样喜欢糖浆！最大化煎饼堆中所有暴露在外的煎饼表面积是最好的，因为暴露的表面积越多，能倒上美味糖浆的地方就越多。任何没有与其他煎饼或盘子接触的煎饼部分都被视为暴露在外。

如果你最优地选择这 $K$ 张煎饼，能获得的最大总暴露煎饼表面积是多少？

## 说明/提示

**样例解释**

在样例 1 中，"堆叠" 只包含一张煎饼。只用第一张煎饼时，暴露表面积为 $\pi \times R_0^2 + 2 \times \pi \times R_0 \times H_0 = 14000\pi \text{ mm}^2$。只用第二张煎饼时，暴露表面积为 $44000\pi \text{ mm}^2$。因此，使用第二张煎饼更优。

在样例 2 中，我们可以使用样例 1 中的两张煎饼。第一张煎饼贡献了顶部面积和侧面积，总共 $14000\pi \text{ mm}^2$。第二张煎饼贡献了部分顶部面积（未被第一张煎饼覆盖的部分）和侧面积，总共 $34000\pi \text{ mm}^2$。合计暴露表面积为 $48000\pi \text{ mm}^2$。

在样例 3 中，所有煎饼的半径均为 100，高度均为 10。如果叠放两张这样的煎饼，实际上就相当于一个半径为 100、高度为 20 的新圆柱体。暴露表面积为 $14000\pi \text{ mm}^2$。

在样例 4 中，最优的堆叠方式是选择半径为 8 和 9 的煎饼。

**数据范围**

- $1 \leq T \leq 100$。
- $1 \leq K \leq N$。
- $1 \leq R_i \leq 10^6$，对于所有 $i$。
- $1 \leq H_i \leq 10^6$，对于所有 $i$。

**小数据范围（9 分，测试点 1 - 可见）**

- $1 \leq N \leq 10$。

**大数据范围（16 分，测试点 2 - 隐藏）**

- $1 \leq N \leq 1000$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
2 1
100 20
200 10
2 2
100 20
200 10
3 2
100 10
100 10
100 10
4 2
9 3
7 1
10 1
8 4```

### 输出

```
Case #1: 138230.076757951
Case #2: 150796.447372310
Case #3: 43982.297150257
Case #4: 625.176938064```

# 题解

## 作者：libu2333 (赞：2)

## 题目大意

从 $N$ 张煎饼里选出 $K$ 张，按照半径从大到小的顺序叠起来，要求总的暴露表面积（顶部暴露的面积 + 侧面积）最大。

## 题意分析

很明显，计算每个煎饼暴露出来的顶面积肯定很麻烦，所以这里我们要~~用小学奥数的知识~~优化一下。注意到，题目中要求煎饼按照半径从大到小的顺序叠起来，所以所有煎饼暴露在外的顶面积加起来**就是最下面半径最大煎饼的顶 / 底面积**！于是这道题就很简单了。


## 解题思路

我们按半径降序先排一遍，然后依次枚举每一个煎饼作为底部的煎饼。

每当确定一个底部煎饼时，我们就只能从它后面的煎饼（半径更小的）里再选出 $K - 1$ 张，去叠在它上面。

上面的每块煎饼只有侧面积参与计算，所以自然是优先选侧面积最大的就行。

所以整个流程就是：

1. 按半径降序排序。
2. 枚举每张煎饼作为底部。
3. 从剩下半径更小的煎饼中选出 $K - 1$ 个侧面积最大的。
4. 把底部的底面积、自己的侧面积和上面那 $K - 1$ 张的侧面积加起来，维护一个最大值即可，注意输出格式。

总体时间复杂度 $O(TN^2 \log N)$，对于该题来说绰绰有余。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const long double pi=3.1415926535897932384626; // π 
ll t,n,k;
struct Node{ //煎饼 
	ll r,h;
	const bool operator>(const Node& b)const{ // 为了使用 greater<Node> 
		return r==b.r?h>b.h:r>b.r;
	}
} a[1005];
int main(){
	cin>>t;
    for(int tt=1;tt<=t;tt++){ // 测试点编号 
    	cin>>n>>k;
        for(int i=0;i<n;i++){
        	cin>>a[i].r>>a[i].h;
        }
        sort(a,a+n,greater<Node>());
        double maxx=0.0;
        for(int i=0;i<n;i++){
            ll r=a[i].r;
            ll h=a[i].h;
            double topx=pi*r*r;
            double sidex=2.0*pi*r*h;
            vector<double> tops;
            if(k==1){
                maxx=max(maxx,topx+sidex);
                continue;
            }
            for(int j=0;j<n;j++){
            	if(j==i)continue;
                if(a[j].r<=r){
                    tops.push_back(2.0*pi*a[j].r*a[j].h);
                }
            }
            sort(tops.begin(),tops.end(),greater<double>());
            double sum=0.0;
            int cnt=0;
            for(double i:tops){
                sum+=i;
                if(++cnt==k-1) break;
            }
            if(cnt==k-1){
                maxx=max(maxx,topx+sidex+sum);
            }
        }
        cout<<fixed<<setprecision(9); // 控制小数位数 
        cout<<"Case #"<<tt<<": "<<maxx<<endl;
    }
    return 0;
}
```

---

## 作者：signed_long_long (赞：1)

# 题目解法

把第二个样例的俯视图画出来看一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/9f8td01f.png)

可以发现，摆出来的上面的面积一定就是最下面的煎饼的上面的面积。

所以，只要枚举一下最下面的煎饼，再选出其余侧面积最大的 $k-1$ 个煎饼即可。答案就是最大值。

注意输出格式！

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,k;
const int N=1e3+10;
int r[N],h[N];
struct node{
	double up,ce;
	double zong;
}g[N];
const double pi=3.1415926535898;
bool cmp(node a,node b){return a.ce>b.ce;}
void work(int qwert){
	printf("Case #%d: ",qwert);
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>r[i]>>h[i];
		g[i].up=1.0*pi*pow(r[i],2);
		g[i].ce=2.0*pi*r[i]*1.0*h[i];
		g[i].zong=g[i].ce+g[i].up;
	}
	sort(g+1,g+n+1,cmp);
	double now,ans=0;
	for(int i=1;i<=n;i++){
		now=0;
		now+=g[i].zong;
		int nowj=1;
		for(int j=1;j<k;j++,nowj++){//注意：侧面积前 k-1 大的煎饼可能包含现在枚举到的，要特判
			if(nowj==i) nowj++;
			now+=g[nowj].ce;
		}
		ans=max(ans,now);
	}
	printf("%.10f\n",ans);
}
int main(){
	cin>>T;
	for(int i=1;i<=T;i++) work(i);
	return 0;
}
```

---

