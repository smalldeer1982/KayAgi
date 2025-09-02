# 题目信息

# [ICPC 2022 Xi'an R] Clone Ranran

## 题目描述

然然需要准备一场有 $c$ 个问题的比赛！他可以进行两种操作：

- 在 $a$ 分钟内克隆一个自己；
- 在 $b$ 分钟内准备好一个问题。

克隆的然然也可以进行上述操作，但然然不能同时进行这两个操作。

然然希望尽快准备好比赛，但是他很懒，所以他让你求出准备比赛的最小分钟数。

共有 $T$ 组数据。

$1\leq T\leq 10 ^ 5$，$1\leq a, b, c\leq 10 ^ 9$。

## 样例 #1

### 输入

```
5
1 1 1
2 3 3
9 9 9
3 26 47
1064 822 1048576
```

### 输出

```
1
7
45
44
21860
```

# AI分析结果

### 算法分类
贪心

### 综合分析与结论
本题的核心逻辑是通过贪心策略选择最优的操作顺序，以最小化准备比赛的时间。所有题解都采用了类似的思路：优先执行克隆操作，然后再执行准备问题的操作。通过枚举克隆次数，计算每种情况下的总时间，并取最小值。

### 所选题解
#### 1. 作者：lailai0916 (赞：5)
- **星级**: 5星
- **关键亮点**: 思路清晰，代码简洁，优化程度高。通过枚举克隆次数（最多30次），计算每种情况下的总时间，并取最小值。
- **个人心得**: 无

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const ll inf=0x3f3f3f3f3f3f3f3f;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
	{
		ll a,b,c;
		cin>>a>>b>>c;
		ll ans=inf;
		for(int i=0;i<=30;i++)
		{
			ans=min(ans,i*a+(c+(1ll<<i)-1)/(1ll<<i)*b);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

#### 2. 作者：Lovely_Elaina (赞：1)
- **星级**: 4星
- **关键亮点**: 通过模拟克隆和准备问题的过程，计算每种情况下的总时间，并取最小值。代码实现较为直观。
- **个人心得**: 无

```cpp
#include <iostream>
#define min(a,b) (a<b?a:b)
#define int long long
#define endl '\n'
using namespace std;

int a,b,c;
int t,mi;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> t;
    while(t--){
        mi = (int)1e15;
        cin >> a >> b >> c;

        int x = 1;
        for(int i = 0; i <= 34; i++){
            mi = min(mi,a*i+b*((c-1)/x+1));
            x *= 2;
        }
        
        cout << mi << endl;
    }
    return 0;
}
```

#### 3. 作者：Smg18 (赞：0)
- **星级**: 4星
- **关键亮点**: 通过循环模拟克隆和准备问题的过程，计算每种情况下的总时间，并取最小值。代码实现较为简洁。
- **个人心得**: 无

```cpp
#include<iostream>
#define ll long long
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;

const int N=1e5+10,NN=1e3+10;
ll n,m,k,x,y,cnt,len,T,ans;
ll minn=0x3f3f3f,maxn=0;
ll arr[N];

signed main(){
	Test;
	cin>>T;
	
	while(T--){
		ll a,b,c;
		cin>>a>>b>>c;
		maxn=b*c;
		for(int i = 1;1<<i-1<=c;i++){
			maxn=min(maxn,i*a+(c+(1<<i)-1)/(1<<i)*b);
		}
		cout<<maxn<<"\n";
	}
	return 0;
}
```

### 最优关键思路或技巧
- **贪心策略**: 优先执行克隆操作，然后再执行准备问题的操作。
- **枚举优化**: 通过枚举克隆次数（最多30次），计算每种情况下的总时间，并取最小值。

### 可拓展之处
- 类似问题可以扩展到其他需要优化操作顺序的场景，如任务调度、资源分配等。

### 推荐题目
1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

这些题目都涉及到贪心策略和优化操作顺序，可以帮助进一步理解和应用贪心算法。

---
处理用时：27.86秒