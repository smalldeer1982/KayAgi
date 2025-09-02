# 题目信息

# Splitting Items

## 题目描述

Alice 和 Bob 有 $n$ 个数，第 $i$ 个数为 $a_i$，他们决定玩一个游戏取走这些数。

游戏由 Alice 开始取数。

每一次玩家都可以拿走一个剩下的数，直到没有数字可拿走。

定义 $A$ 是 Alice 获取的数字和，$B$ 是 Bob 获取的数字和，游戏总分 $p = A - B$。

Alice 希望最大化 $p$，Bob 希望最小化 $p$，他们都绝顶聪明。

现在 Bob 拥有了修改数的权限，可以把一些数字（可以没有，也可以没有全部）**增加**一个整数值（可以增加不同的值），但是这样 Alice 可能会起疑心，所以总增加的数值必须小于等于 $k$。

请求出 Bob 能达到的 $p$ 的最小值。

## 样例 #1

### 输入

```
4
2 5
1 10
3 0
10 15 12
4 6
3 1 2 4
2 4
6 9```

### 输出

```
4
13
0
0```

# AI分析结果

【题目内容】
# 物品分配

## 题目描述

爱丽丝（Alice）和鲍勃（Bob）有 $n$ 个数，第 $i$ 个数为 $a_i$，他们决定玩一个游戏来取走这些数。

游戏由爱丽丝先开始取数。

每次玩家都可以拿走一个剩下的数，直到没有数字可拿。

定义 $A$ 是爱丽丝获取的数字和，$B$ 是鲍勃获取的数字和，游戏总分 $p = A - B$。

爱丽丝希望最大化 $p$，鲍勃希望最小化 $p$，且他们都绝顶聪明。

现在鲍勃拥有了修改数的权限，可以把一些数字（可以没有，也可以是全部）**增加**一个整数值（可以对不同数字增加不同的值），但是这样爱丽丝可能会起疑心，所以总增加的数值必须小于等于 $k$。

请求出鲍勃能达到的 $p$ 的最小值。

## 样例 #1

### 输入

```
4
2 5
1 10
3 0
10 15 12
4 6
3 1 2 4
2 4
6 9
```

### 输出

```
4
13
0
0
```

【综合分析与结论】
这些题解的核心思路基本一致，都是基于贪心算法。由于爱丽丝和鲍勃都想取到尽可能大的数，所以先将数组降序排序，爱丽丝会取排序后奇数下标的数，鲍勃会取偶数下标的数。鲍勃修改数字时，为了不改变数字的相对大小（避免修改后的数字被爱丽丝取走），会尽量让偶数下标的数与它前一个奇数下标的数相等，直到 $k$ 用完。

算法要点：
1. 对数组进行降序排序。
2. 遍历偶数下标的数，根据 $k$ 的剩余量进行修改。
3. 计算修改后奇数下标数的和与偶数下标数的和，相减得到结果。

解决难点：
1. 确定修改策略，保证鲍勃修改数字后不会改变数字的相对大小，从而确保修改的数字能被自己取到。
2. 合理使用 $k$，在 $k$ 不足时进行特殊处理。

评分：
- GY程袁浩：4星。思路清晰，代码简洁，直接计算出未修改前的分数，再减去可修改的部分，逻辑巧妙。
- Stars_Traveller：4星。思路明确，代码可读性高，按照常规步骤进行排序、修改、计算答案。
- Redamancy_Lydic：4星。思路清晰，有输入优化，代码结构良好。

【所选题解】
- GY程袁浩（4星）：关键亮点在于直接计算未修改前的分数，然后减去可修改的部分，避免了对数组元素的实际修改，简化了代码。
- Stars_Traveller（4星）：思路明确，代码按照常规步骤实现，可读性高，易于理解。
- Redamancy_Lydic（4星）：使用了输入优化，代码结构良好，逻辑清晰。

【重点代码】
### GY程袁浩
```cpp
#include <bits/stdc++.H>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],n,k,ans,sum;
signed main() {
    int tt;
    cin>>tt;
    while(tt--) {
        cin>>n>>k;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+1+n);
        reverse(a+1,a+1+n);
        for(int i=1;i<=n;i+=2) {
            if(i==n) {
                ans+=a[i];
                break;
            }
            sum+=a[i]-a[i+1];
            ans+=a[i]-a[i+1];
        }
        cout<<ans-min(sum,k)<<endl;
        sum=0,ans=0;
    }
    return 0;
}
```
核心思想：先对数组降序排序，然后计算未修改前奇数下标数与偶数下标数的差值和，最后用这个和减去 $k$ 与差值和的较小值，得到结果。

### Stars_Traveller
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000005], n, k, t;
bool cmp(int x, int y){return x>y;}
signed main()
{
    for(cin>>t;t;t--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++)cin>>a[i];
        sort(a+1,a+1+n,cmp);
        for(int i=2;i<=n;i+=2)
        {
            if(k>=a[i-1]-a[i])
            {
                k-=a[i-1]-a[i];
                a[i]=a[i-1];
            }
            else
            {
                a[i]+=k;
                break;
            }
        }
        int cnt=0;
        for(int i=1;i<=n;i++)
        {
            if(i&1)
            {
                cnt+=a[i];
            }
            else cnt-=a[i];
        }
        cout<<cnt<<"\n";
    }
}
```
核心思想：先对数组降序排序，然后遍历偶数下标的数，根据 $k$ 的剩余量进行修改，最后计算奇数下标数的和与偶数下标数的和的差值，得到结果。

### Redamancy_Lydic
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int mod=998244353;
const int maxn=1e6+10;
const int inf=1e17;
const double eps=1e-10;
int n,k,a[maxn];
void Main()
{
	n=read(),k=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	sort(a+1,a+n+1);
	reverse(a+1,a+n+1);
	for(int i=2;i<=n;i+=2)
	{
		int delta=a[i-1]-a[i];
		if(delta<=k)
		{
			a[i]=a[i-1];
			k-=delta;
		}
		else
		{
			a[i]+=k;
			break;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i+=2)ans=ans+a[i];
	for(int i=2;i<=n;i+=2)ans=ans-a[i];
	cout<<ans<<endl;
}
signed main()
{
	int T=read();
	while(T--)Main();
	return 0;
}
```
核心思想：使用输入优化读取数据，对数组降序排序，遍历偶数下标的数进行修改，最后计算奇数下标数的和与偶数下标数的和的差值，得到结果。

【最优关键思路或技巧】
1. 贪心策略：通过分析双方的最优取数策略，确定鲍勃的修改策略，即尽量让偶数下标的数与它前一个奇数下标的数相等。
2. 排序优化：对数组进行降序排序，方便确定双方的取数顺序。

【拓展思路】
同类型题或类似算法套路：
1. 博弈类问题：通常需要分析双方的最优策略，然后根据策略进行计算。
2. 贪心算法：在满足一定条件下，通过局部最优解得到全局最优解。

【推荐题目】
1. P1223 排队接水：考察贪心算法，通过合理排序得到最优解。
2. P1094 纪念品分组：考察贪心算法，通过合理分组得到最优解。
3. P1803 凌乱的yyy / 线段覆盖：考察贪心算法，通过合理选择线段得到最优解。

【个人心得】
这些题解中均未包含个人心得（调试经历、踩坑教训、顿悟感想等）。

---
处理用时：49.59秒