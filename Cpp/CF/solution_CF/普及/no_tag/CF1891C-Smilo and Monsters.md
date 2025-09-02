# Smilo and Monsters

## 题目描述

在 Smilo 的游戏中，有 $n$ 群怪兽，第 $i$ 群怪兽的数量为 $a_i$。游戏的目标是消灭所有的怪兽，有两种攻击方式：

- 普攻：任选一群怪兽，击杀其中的一只，并让连击点数 $x$ 增加 $1$。
- 大招：选择一群数量不小于 $x$（$x$ 是目前的连击点数）的怪兽，击杀其中的 $x$ 只，并让连击点数归零。

一次普攻或一次大招记作一次攻击。初始连击点数为 $0$，请求出消灭所有怪兽的最少攻击次数。

## 样例 #1

### 输入

```
4
4
1 3 1 1
4
1 2 1 1
6
3 2 1 5 2 4
2
1 6```

### 输出

```
4
4
11
5```

# 题解

## 作者：_cpp (赞：11)

## Part 1：思路

一道贪心加一点点分类讨论题。对于每一组数据，大招的最佳释放次数是 $\begin{aligned} \lfloor \frac{\sum _ {i=1}^{n} {a[i]}}{2} \rfloor\end{aligned}$。可以理解为打一半的怪攒能量，再用大招将剩下一半怪秒掉。接下来将怪群从大到小排序一下，会产生两种情况：

1.连击点数大于最大的怪群，可以直接将此怪群秒掉，再继续秒下一个。见代码（其中 s 为连击点数）：
```cpp
if(s >= a[i]){
	s -= a[i]; // 大招可以秒掉的怪群，直接秒
   	a[i] = 0;
}
```


2.连击点数小于最大的怪群中怪的数量，没办法，只能先秒一部分，剩下的用普攻慢慢打。
另外还用注意的是本题要开 long long。

## Part 2：代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,a[200010],s;
int main()
{
    cin >> t;
    while(t--){
        cin >> n;
        s = 0;
        for(int i = 1;i <= n;i++) scanf("%lld",&a[i]),s += a[i];
        sort(a + 1,a + n + 1);
        s /= 2;//计算最大连击次数
        long long ans = 0;
        for(int i = n;i >= 1;i--){
            if(!s) break;
            if(s >= a[i]){
                s -= a[i]; // 大招可以秒掉的怪群，直接秒
                a[i] = 0;
                ans++;
            }
            else{ //大招不能秒掉的怪群，秒掉其中一些
                a[i] -= s;
                ans++;
                break;
            }
        }
        for(int i = 1;i <= n;i++) ans += a[i]; //剩下的全得用普攻解决
        cout << ans << "\n";
    }
	return 0;
}
```


---

## 作者：Vct14 (赞：5)

贪心题。我们可以先不停地普攻当前数量最少的怪兽攒连击点数，等连击点数等于当前数量最多的怪兽只数时，用大招将它们全部击杀。

因此我们将前面的一些较少的怪兽与最后较大的怪兽配对即可。这样大招总共会杀死一半（下取整）的怪兽。

那么反向思考，已知大招的能量为怪兽数量的一半。那么从最多的怪兽开始，能用大招杀就杀。剩余的怪兽就只能用普攻杀。

---

## 作者：Fasfree (赞：4)

根据题意可知操作一的贡献固定为一，因此我们需要最大化操作二的价值，我们对血量进行排序。设当前数列中最大的数字为 $m$ ，显然每次贪心的选择使用操作一操作当前最小的数字，当 $x = m$ 时使用操作二将其消除，能够最大化操作二的价值

当数列中仅剩最后一个数字，显然使用若干次操作一后再使用一次操作二将其消去是最优的。设需要用操作一操作 $b$ 次，当前剩下第 $i$ 个数字，则    $b=\lfloor{\frac{a_i-x}{2}}\rfloor$ 。注意如果 $a_i$ 为奇数，这样操作完后 $a_i$ 为一，此时需要再使用一次操作一将其消去
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200005;
ll s[N];
int main(){
	ll t, n;
	scanf("%lld", &t);
	while (t--){
		ll ans=0;
		scanf("%lld", &n);
		for (ll x=1;x<=n;++x){
			scanf("%lld", &s[x]);
		}
		ll pw=0, i=n;
		sort(s+1, s+1+n);
		for (ll x=1;x<=i;++x){
			while (s[x]){
				if (x != i){
					if (s[x]+pw < s[i]){
						ans += s[x];
						pw += s[x];
						s[x] = 0;

					} else {
						ans += s[i]-pw;
						s[x] -= s[i] - pw;
						ans += 1;
						s[i] = 0;
						--i;
						pw=0;
					}
				} else {
					if (s[x] > 1){ // pw+x==n-x
					ans += ((s[x]-pw)/2);
					s[x] -= ((s[x]-pw)/2)+pw+((s[x]-pw)/2);
					++ans;
				}
					
					if (s[x])++ans, --s[x];
				}
			}
		}
		printf("%lld\n", ans);
	}
	
}
```


---

## 作者：BugGod (赞：2)

考虑贪心。显然，我们可以打一些小怪，攒大招，然后一个大招全扫掉。显然，我们留 $\lfloor{\frac{\sum a_i}{2}}\rfloor$ 的血量给大招最合适（其实就是能给大招的最多血量），那么我们可以将血量从大到小排序，一个一个消耗大招的能量即可。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[200010],boom,ans;
int cmp(int x,int y)
{
	return x>y;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		ans=boom=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)boom+=a[i];
		boom>>=1;//大招的能量
		for(int i=1;i<=n;i++)
		{
			if(boom>=a[i])//大招能打死
			{
				boom-=a[i];
				a[i]=0;
			}
			else if(boom>0)//只能刮痧
			{
				a[i]-=boom;
				boom=0;
			}
			else break;
			ans++;
		}
		for(int i=1;i<=n;i++)ans+=a[i];//剩余小怪的血量就是A的次数
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：SunnyYuan (赞：2)

建议标签：贪心

## 思路

贪心题，首先我们可以想到可以使用较小的怪物群组合出 $x$ 然后用 $1$ 的代价干掉当前最大的怪物群，直到所有较小的怪物加起来都不能干掉最大的怪物时，才要特判。

当所有较小的怪物加起来都不能干掉最大的怪物时，如果当前已经积累了 $x$ 个怪物，现在只剩下一个最大的怪物群，有 $t$ 只怪物，那么我们不妨将他们两个加起来考虑。

![](https://cdn.luogu.com.cn/upload/image_hosting/s2rfp80r.png)

$t + x$ 如果是偶数，那么先消灭 $s = \left\lfloor\dfrac{t + x}{2}\right\rfloor$，然后再用 $1$ 的代价消灭 $s$ 只怪物，如果 $s$ 是奇数，那么还会多 $1$，所以答案再加 $1$。

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: C. Smilo and Monsters
| OJ:      Codeforces - Codeforces Round 907 (Div. 2)
| URL:     https://codeforces.com/contest/1891/problem/C
| When:    2023-11-01 10:03:36
| 
| Memory:  256 MB
| Time:    1000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());
    int l = 0, r = n - 1, sum = 0;
    i64 ans = 0;
    while (l <= r) {
        while (l < r && sum < a[r]) {
            int add = min(a[r] - sum, a[l]);
            sum += add;
            a[l] -= add;
            if (!a[l]) l++;
        }
        if (sum == a[r]) {
            ans += sum + 1;
            a[r] = sum = 0;
            r--;
        }
        if (l == r) {
            // cout << l << ' ' << r << ' ' << a[l] << endl;
            int p = sum + a[l];
            if (p & 1) ans += (p / 2) + 1 + (bool)(p / 2);
            else ans += (p / 2) + 1;
            break;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}

```

---

## 作者：tai_chi (赞：1)

大力贪心，给怪物按血量排递增序，用普攻打小的攒能量，用技能一波干死大的。可以用双指针一个往后扫一个往前扫，实现要注意一些细节。

其实还有更漂亮的做法，发现如果安排合理，一半的伤害是技能打出，一半的伤害是普攻打出，这样可以最大限度减少浪费的技能点。

可以把总伤害（怪物总血量）的一半下取整用作技能，遍历统计即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define endl '\n'
#define IOS                     \
	ios::sync_with_stdio(NULL); \
	cin.tie(NULL);              \
	cout.tie(NULL)
void solve()
{
	int n, sum = 0;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		sum += a[i];
	}
	sum /= 2; // 技能伤害
	sort(a.begin() + 1, a.end());
	int ans = 0;
	for (int i = n; i >= 1; i--)
	{
		if (sum >= a[i])
			sum -= a[i], a[i] = 0, ans++;
		else if (sum)
			a[i] -= sum, sum = 0, ans++;
	}
	for (int i = 1; i <= n; i++)
		ans += a[i];
	cout << ans << endl;
}

signed main()
{
	IOS;
	int T;
	cin >> T;
	while (T--)
	{
		solve();
	}
	return 0;
}

```

---

