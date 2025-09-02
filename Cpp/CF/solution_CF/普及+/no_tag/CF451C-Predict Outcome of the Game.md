# Predict Outcome of the Game

## 题目描述

There are $ n $ games in a football tournament. Three teams are participating in it. Currently $ k $ games had already been played.

You are an avid football fan, but recently you missed the whole $ k $ games. Fortunately, you remember a guess of your friend for these $ k $ games. Your friend did not tell exact number of wins of each team, instead he thought that absolute difference between number of wins of first and second team will be $ d_{1} $ and that of between second and third team will be $ d_{2} $ .

You don't want any of team win the tournament, that is each team should have the same number of wins after $ n $ games. That's why you want to know: does there exist a valid tournament satisfying the friend's guess such that no team will win this tournament?

Note that outcome of a match can not be a draw, it has to be either win or loss.

## 说明/提示

Sample 1. There has not been any match up to now $ (k=0,d_{1}=0,d_{2}=0) $ . If there will be three matches (1-2, 2-3, 3-1) and each team wins once, then at the end each team will have 1 win.

Sample 2. You missed all the games $ (k=3) $ . As $ d_{1}=0 $ and $ d_{2}=0 $ , and there is a way to play three games with no winner of tournament (described in the previous sample), the answer is "yes".

Sample 3. You missed 4 matches, and $ d_{1}=1,d_{2}=0 $ . These four matches can be: 1-2 (win 2), 1-3 (win 3), 1-2 (win 1), 1-3 (win 1). Currently the first team has 2 wins, the second team has 1 win, the third team has 1 win. Two remaining matches can be: 1-2 (win 2), 1-3 (win 3). In the end all the teams have equal number of wins (2 wins).

## 样例 #1

### 输入

```
5
3 0 0 0
3 3 0 0
6 4 1 0
6 3 3 0
3 3 3 2
```

### 输出

```
yes
yes
yes
no
no
```

# 题解

## 作者：ZLCT (赞：0)

# CF451C Predict Outcome of the Game
## 题意
一共有三个队进行 $n$ 场比赛，给出 $k$ 场比赛后 $1,2$ 队胜场差值的绝对值 $d1$ 和 $2,3$ 队胜场差值的绝对值 $d2$，问有没有可能最后三队的胜场数相等。
## solution
首先我们发现 $n$ 必须是 $3$ 的倍数，否则不可能三队的胜场相等。\
接下来很显然三个队的胜场数就是 $\displaystyle\frac{n}{3}$。\
于是我们再来分析给出的 $d1,d2$。既然它给我们的是绝对值，并且一共只有两个，那我们就尝试直接枚举绝对值的正负并 check 即可。（下文第一个代表 $d1$ 符号，第二个代表 $d2$ 符号）\
假设第一个球队目前胜场为 $x$。
- $(+,+)$：三只球队得分分别为 $x,x+d1,x+d1+d2$。
- $(+,-)$：三只球队得分分别为 $x,x+d1,x+d1-d2$。
- $(-,+)$：三只球队得分分别为 $x,x-d1,x-d1+d2$。
- $(-,-)$：三只球队得分分别为 $x,x-d1,x-d1-d2$。
### check
我们通过题意知道三支球队胜场和为 $k$，$d1,d2$ 通过枚举也固定了，于是对于每一种情况，我们都可以求出 $x$ 的值。至于合法就是 $x$ 是个整数且每个球队的胜场数都在 $[0,\displaystyle\frac{n}{3}]$ 之间，因为只有这样我们才可以补齐到 $\displaystyle\frac{n}{3}$。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,d1,d2;
bool check(int x,int y){
    int z=k-x-y;
    if(z%3)return 0;
    z/=3;
    if(z<0||z+x<0||z+y<0)return 0;
    if(z<=n&&z+x<=n&&z+y<=n)return 1;
    return 0;
}
void solve(){
    cin>>n>>k>>d1>>d2;
    if(n%3){
        cout<<"no\n";
        return;
    }
    n/=3;
    if(check(d1,d1+d2)|check(d1,d1-d2)|check(-d1,-d1+d2)|check(-d1,-d1-d2)){
        cout<<"yes\n";
    }else{
        cout<<"no\n";
    }
    return;
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：_Kimi_ (赞：0)

# CF451C题解

### 题意

一共有 $n$ 场比赛，已经进行了 $k$ 场比赛。一共有三支队伍，第一支队伍与第二支队伍胜场的差是 $d_1$，第二支队伍与第三支队伍胜场的差是 $d_2$，问是否可以所有比赛结束后三支队伍的胜场一样。

### 思路

一共有四种可能：

1. 比赛结果为：$a$，$a + d_1$，$a + d_1 + d_2$。
2. 比赛结果为：$a$，$a + d_1$，$a + d_1 - d_2$。
3. 比赛结果为：$a$，$a - d_1$，$a - d_1 - d_2$。
4. 比赛结果为：$a$，$a + d_1$，$a + d_1 - d_2$。

枚举四种可能就可以了。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
bool check(ll n, ll k, ll a, ll b){
	k -= a + b;
	if(k % 3 != 0) return 0;
	k /= 3;
	if(k < 0 || k + a < 0 || k + b < 0) return 0;
	if(k <= n && k + a <= n && k + b <= n) return 1;
	return 0;
}
int main(){
	cin >> t;
	while(t--){
		ll n, k, d, dd;
		cin >> n >> k >> d >> dd;
		if(n % 3 != 0){
			cout << "no" << endl;
			continue;
		}
		n /= 3;
		if(check(n, k, d, d + dd) || check(n, k, d, d - dd) || check(n, k, -d, dd - d) || check(n, k, -d, -d - dd)) cout << "yes" << endl;
		else cout << "no" << endl;
	}
	return 0;
}
```


---

