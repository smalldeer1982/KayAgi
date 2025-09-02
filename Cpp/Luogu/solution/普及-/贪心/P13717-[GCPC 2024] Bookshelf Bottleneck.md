# [GCPC 2024] Bookshelf Bottleneck

## 题目描述

Brianna 是一个书虫。在家里，她有一个装满了她最喜欢的书的大书架。她的藏书非常丰富，从侦探小说、科幻小说到传记应有尽有。

最近，Brianna 又收集了 $n$ 本漫画小说。然而，这些新书目前随处乱放，在地板上堆成了高高的书堆。与此同时，其中一块书架板上积满了灰尘和一些不属于那里的家用杂物。新书就这样随意堆放，Brianna 终于受不了了，决定把它们放到这块书架板上。为此，她首先需要在书架板上腾出空间。

:::align{center}
![图 B.1：样例输入 3 的可视化。](https://cdn.luogu.com.cn/upload/image_hosting/atblbkye.png)
图 B.1：样例输入 3 的可视化。
:::

Brianna 想要把这些书排成一条水平直线，不能把多本书叠在一起。虽然书架足够宽，能容纳所有的书，但清理书架需要花费时间。因此，Brianna 想要最小化她需要清理的书架部分的宽度。

每本书都可以用一个长方体来描述，具有三条边长 $l$、$w$ 和 $h$。由于书架板上方的空间受到上方书架板的限制，只有当一本书的竖直边长不超过两块书架板之间的距离 $H$ 时，才能竖直放置。Brianna 可以任意旋转每本书。保证书架的深度足够，无论怎么放书都不会掉下来。然而，所有的书都必须平稳地放在书架板上，也就是说，每本书必须有一个完整的面与书架板接触，而不能只用一条边接触。

Brianna 的书最少需要多宽的书架空间？

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 3
10 2 5```

### 输出

```
5```

## 样例 #2

### 输入

```
1 3
10 4 5```

### 输出

```
impossible```

## 样例 #3

### 输入

```
2 10
10 2 10
2 3 4```

### 输出

```
4```

## 样例 #4

### 输入

```
3 1000000000
1000000000 1000000000 1000000000
1000000000 1000000000 1000000000
1000000000 1000000000 1000000000```

### 输出

```
3000000000```

# 题解

## 作者：__CuSO4__ (赞：1)

### 题意简述

给你 $n$ 个立方体，具有三个边长 $l$、$w$ 和 $h$，可以任意旋转每个立方体的三维方向。只有当立方体的高不超过 $H$ 时，才能将立方体竖直放置，求摆放所有立方体所需的宽度和是多少？

### 思路

对于每个立方体，我们要在能放的情况下使得：
- 把尽可能大的一条边当作高。
- 把尽可能小的一条边当作宽。

根据这个贪心策略，用几个判断就能过了。

::::warning[注意]{open}
要开 `long long`，$10^9\times 10^9=10^{18}$，会爆 `int`。
::::

### 代码

```cpp line-numbers lines=2-2
#include <iostream>
#define int long long //注意
using namespace std;

int n, h, ans;

signed main() {
    cin >> n >> h;
    while (n--) {
        int x, y, z;
        cin >> x >> y >> z;
        //相当于排序
        int a = min(x,min(y,z)), c = max(x,max(y,z)), b = x+y+z-a-c;
        //根据贪心策略进行选择
        if (c <= h) ans += a;
        else if (b <= h) ans += a;
        else if (a <= h) ans += b;
        else { //如果三条边都放不了，说明不合法
            puts("impossible");
            return 0;
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题目分析
本题要求计算将所有漫画书放置在书架上所需的最小总宽度，同时确保每本书的垂直高度不超过书架的高度限制 $H$。  
每本书为长方体，可自由旋转（即选择任意一个面作为底面接触书架），但必须保证垂直高度（与书架垂直的维度）不超过 $H$。
## 解题思路
- 分析单本书的放置可能性：对于每本书的三个维度 $l, w, h$，有 $3$ 种可能的放置方式（分别以三个维度作为垂直高度）：
  - 若以 $a$ 为高度，则宽度为另外两个维度中的较小值。
  - 若以 $b$ 为高度，则宽度为另外两个维度中的较小值。
  - 若以 $c$ 为高度，则宽度为另外两个维度中的较小值。
- 排序优化：将三个维度排序为 $a ≤ b ≤ c$ 后，可简化判断逻辑：
  - 可能的高度选择为 $a, b, c$。
  - 对应的宽度分别为 $b, a, a$。（因为排序后较小的维度已确定）
- 合法性检查：对于每种高度选择，需满足高度 $≤ H$，否则该放置方式不合法。
- 最小宽度计算：在所有合法的放置方式中，选择宽度最小的方案；若没有合法方案，则整体结果为 `impossible`。
## 思路证明
::::info[思路证明]
:::info[定理]
__定理__：对排序后的维度 $a ≤ b ≤ c$，最优放置方式为：
- 若 $b ≤ H$：选择以 $b$ 为高度（宽度 $a$）。
- 若 $b > H$ 但 $c ≤ H$：选择以 $c$ 为高度（宽度 $a$）。
- 若 $c > H$：无法放置。
:::
:::info[证明]
- 排序后 $a ≤ b ≤ c$，所有可能的合法放置方式及宽度：
  - 高度 $a$（合法需 $a ≤ H$）→ 宽度 $b$（因为 $b ≤ c$）。
  - 高度 $b$（合法需 $b ≤ H$）→ 宽度 $a$（因为 $a ≤ c$）。
  - 高度 $c$（合法需 $c ≤ H$）→ 宽度 $a$（因为 $a ≤ b$）。
- 比较三种方式的宽度：$a ≤ b$（由排序性质），因此：  
  - 当 $b ≤ H$ 时，高度 $b$ 对应宽度 $a$ 是最小值。
  - 当 $b > H$ 但 $c ≤ H$ 时，只能选择高度 $c$，宽度 $a$。
  - 当 $c > H$ 时，无合法放置方式。
:::
::::
## AC代码
```
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0),cin.tie(0);
    int n, H;
    cin >> n >> H;
    long long total_width = 0;
    bool possible = true;
    for (int i = 0; i < n; ++i) {
        long long l, w, h;
        cin >> l >> w >> h;
        long long a = min({l, w, h});
        long long c = max({l, w, h});
        long long b = l + w + h - a - c;
        long long min_width = -1;
        if (a <= H) {
            min_width = b;
        }
        if (b <= H) {
            long long curr = a;
            if (min_width == -1 || curr < min_width) {
                min_width = curr;
            }
        }
        if (c <= H) {
            long long curr = a;
            if (min_width == -1 || curr < min_width) {
                min_width = curr;
            }
        }
        if (min_width == -1) {
            possible = false;
            break;
        }
        total_width += min_width;
    }
    if (possible) {
        cout << total_width << endl;
    } else {
        cout << "impossible" << endl;
    }
    return 0;
}
```
谢谢观看！

---

## 作者：QQ9178 (赞：0)

### 思路：  
这道题很简单，只需要判断 $6$ 种方案哪一种是最小的，并且特判三个数值都大于其书架高度的情况，最终用一个变量累加和。  
### 代码：  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int n, H;
    cin >> n >> H;
    int sum = 0;
    for(int i = 0; i < n; i++) {
        int l, w, h;
        cin >> l >> w >> h;
        int minn = 1e18,a=0;  
        if(h <= H) minn = min(minn, min(l, w)),a=1; 
        if(w <= H) minn = min(minn, min(l, h)),a=1;  
        if(l <= H) minn = min(minn, min(w, h)),a=1;
        if(!a) {
            cout << "impossible";
            return 0;
        }
        sum += minn;
    }
    cout << sum;
    return 0;
}
```

---

## 作者：WritingLetter (赞：0)

## 贪心
看到题目以及标签，我们会发现每一本书籍可以抽象成一个个长方体，假设**三条边**分别是 $a,b,c$，因为可以旋转，所以长宽高的原定义已经不重要了。

旋转后共有以下六种情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/dg3jeq71.png)

如果 $H$ 为无限高，那么我们只需要考虑对于每一本书，取三边最小值即可。

问题在于现在有个限制——书架高度。显然上述六种情况中，如果长方体**目前的高已经超过了书架的高度**，那么当前情况的**宽是不能被采用的**；反之，宽是可以被采用的，六种情况取宽的最小值即可。

### 一些细节：
- 答案是和，所以 `int` 会爆，要开 `long long`。
- 记得判断如果有任意一本书 $a,b,c>H$，则输出 `impossible`。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=1e5+5;//注意范围

int n,H;//书架高度变量名记得与每本书的高度分开
int l[N],w[N],h[N];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);

	cin>>n>>H;
	bool f=true;//判断是否有书无论怎么旋转都无法放置
	for(int i=1;i<=n;i++){
		cin>>l[i]>>w[i]>>h[i];
		if(l[i]>H&&w[i]>H&&h[i]>H)
			f=false;
	}
	if(f==false){//无法放置
		cout<<"impossible";
		return 0;
	}
	
	ll ans=0;//记得开long long
	for(int i=1;i<=n;i++){
		int s=INT_MAX;//求最小值，初始化一个大值
		if(l[i]<=H) //我这里简化了代码，将六种情况分为三大类，以不同高度区分
			s=min(s,min(w[i],h[i]));//每种高度可放置则取最小的宽
		if(w[i]<=H) 
			s=min(s,min(l[i],h[i]));
		if(h[i]<=H) 
			s=min(s,min(w[i],l[i]));
		ans+=s;
	}
	cout<<ans;
	return 0;
}
```
整体就是这样了，如果有不懂或者错误请随时私信我或在评论区指出，感谢！求赞 qwq。

---

## 作者：LG086 (赞：0)

给出书本个数 $N$ 和书架高度 $H$，书架宽度极大，求书架长度的最小值。

一本书是一个长方体，有长、宽、高，可以随意地摆书。我们用 $ans$ 记录答案，用 $a_1,a_2,a_3$ 记录长、宽、高的值，从大到小排序 $a_1,a_2,a_3$。

分情况判断就行。

+ 若 $a_1 \le H$，则书本怎么放都行。要想宽度最小，只需要让 $a_1,a_2,a_3$ 中最小的一个当宽，即 $a_3$。所以 $ans\leftarrow ans+a_3$。
+ 若 $a_1 > H$ 但是 $a_2 \le H$，书本的高度不能大于 $H$，所以只有 $a_2,a_3$ 中的一个可以当高。要使宽最小，显然 $a_3$ 不能当高，它应该做宽。所以 $ans\leftarrow ans+a_3$。
+ 若只有 $a_3 \le H$，书本的高只能是 $a_3$，那么此时最小的宽就是 $\min(a_1,a_2)$，因为我们排序过 $a_1,a_2,a_3$，所以宽就是 $a_2$。所以 $ans\leftarrow ans+a_2$。
+ 若有 $a_1,a_2,a_3 > H$ 的情况，则书本咋放都放不下。所以无解。

下面是核心代码。

```cpp
while(n--){
 cin>>a[0]>>a[1]>>a[2];
 stable_sort(a,a+3,greater<ll>());
 if(a[0]<=H)ans+=a[2];
 else if(a[1]<=H)ans+=a[2];
 else if(a[2]<=H)ans+=a[1];
 else return cout<<"impossible",0;
}
```

---

## 作者：Crazyouth (赞：0)

## 分析

每个书最大的那一维显然没有用，因为如果第二小的那一维放的进书架，那么书架宽度只会增加最小的那一维，否则就把最小的那一维当做高，使宽度增加第二小的那一维（如果三个维度都装不下那么就无解了）。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	int n,h,ans=0;
	cin>>n>>h;
	for(int i=1;i<=n;i++)
	{
		int a[3];
		cin>>a[0]>>a[1]>>a[2];
		sort(a,a+2);
		if(a[0]>h)
		{
			cout<<"impossible";
			return 0;
		}
		ans+=(a[1]>h?a[1]:a[0]);
	}
	cout<<ans;
}

---

