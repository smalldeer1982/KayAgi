# Turtle and Piggy Are Playing a Game 2

## 题目描述

Turtle and Piggy are playing a game on a sequence. They are given a sequence $ a_1, a_2, \ldots, a_n $ , and Turtle goes first. Turtle and Piggy alternate in turns (so, Turtle does the first turn, Piggy does the second, Turtle does the third, etc.).

The game goes as follows:

- Let the current length of the sequence be $ m $ . If $ m = 1 $ , the game ends.
- If the game does not end and it's Turtle's turn, then Turtle must choose an integer $ i $ such that $ 1 \le i \le m - 1 $ , set $ a_i $ to $ \max(a_i, a_{i + 1}) $ , and remove $ a_{i + 1} $ .
- If the game does not end and it's Piggy's turn, then Piggy must choose an integer $ i $ such that $ 1 \le i \le m - 1 $ , set $ a_i $ to $ \min(a_i, a_{i + 1}) $ , and remove $ a_{i + 1} $ .

Turtle wants to maximize the value of $ a_1 $ in the end, while Piggy wants to minimize the value of $ a_1 $ in the end. Find the value of $ a_1 $ in the end if both players play optimally.

You can refer to notes for further clarification.

## 说明/提示

In the first test case, initially $ a = [1, 2] $ . Turtle can only choose $ i = 1 $ . Then he will set $ a_1 $ to $ \max(a_1, a_2) = 2 $ and remove $ a_2 $ . The sequence $ a $ becomes $ [2] $ . Then the length of the sequence becomes $ 1 $ , and the game will end. The value of $ a_1 $ is $ 2 $ , so you should output $ 2 $ .

In the second test case, one of the possible game processes is as follows:

- Initially $ a = [1, 1, 2] $ .
- Turtle can choose $ i = 2 $ . Then he will set $ a_2 $ to $ \max(a_2, a_3) = 2 $ and remove $ a_3 $ . The sequence $ a $ will become $ [1, 2] $ .
- Piggy can choose $ i = 1 $ . Then he will set $ a_1 $ to $ \min(a_1, a_2) = 1 $ and remove $ a_2 $ . The sequence $ a $ will become $ [1] $ .
- The length of the sequence becomes $ 1 $ , so the game will end. The value of $ a_1 $ will be $ 1 $ in the end.

In the fourth test case, one of the possible game processes is as follows:

- Initially $ a = [3, 1, 2, 2, 3] $ .
- Turtle can choose $ i = 4 $ . Then he will set $ a_4 $ to $ \max(a_4, a_5) = 3 $ and remove $ a_5 $ . The sequence $ a $ will become $ [3, 1, 2, 3] $ .
- Piggy can choose $ i = 3 $ . Then he will set $ a_3 $ to $ \min(a_3, a_4) = 2 $ and remove $ a_4 $ . The sequence $ a $ will become $ [3, 1, 2] $ .
- Turtle can choose $ i = 2 $ . Then he will set $ a_2 $ to $ \max(a_2, a_3) = 2 $ and remove $ a_3 $ . The sequence $ a $ will become $ [3, 2] $ .
- Piggy can choose $ i = 1 $ . Then he will set $ a_1 $ to $ \min(a_1, a_2) = 2 $ and remove $ a_2 $ . The sequence $ a $ will become $ [2] $ .
- The length of the sequence becomes $ 1 $ , so the game will end. The value of $ a_1 $ will be $ 2 $ in the end.

## 样例 #1

### 输入

```
5
2
1 2
3
1 1 2
3
1 2 3
5
3 1 2 2 3
10
10 2 5 2 7 9 2 5 10 7```

### 输出

```
2
1
2
2
7```

# 题解

## 作者：Yxy7952 (赞：3)

## 题意
有两个人轮流删除序列 $a$ 中的数。第一个人每次删除序列中最小的数，第二个人每次删除序列中最大的数，求最后剩下的数。

## 思路
由于两个人轮流删除序列中最小和最大的数，所以我们给序列从小到大排序。

排序后观察删除操作，发现每次删除最左边和最右边的数，最后剩下的一定是序列中间的数。

所以代码就很好写了，排序后输出编号为 $\left \lfloor \frac{n}{2}  \right \rfloor +1$ 的数就行了
## 代码

这里使用计数排序，时间复杂度为 $O(n)$。

**注意**：虽然时间复杂度是线形的，但是因为常数问题，这个代码在平均用时上是比其他代码慢的。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T,n;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>T;
	while(T--){
		int t[100005]={0},x,sum=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>x,t[x]++;
		for(int i=1;i<=100000;i++){
			sum+=t[i];
			if(sum>n/2){
				cout<<i<<"\n";
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：zsq9 (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF2003B#submit)

## 题目大意

小乌龟和小猪在玩一个数列游戏。他们得到一个数列 $a_1, a_2, \ldots, a_n$，小乌龟先来。小乌龟和小猪轮流做（小乌龟做第一轮，小猪做第二轮，小乌龟做第三轮，等等）。

游戏过程如下

- 假设当前序列的长度为 $m$。如果是 $m = 1$，游戏结束。
- 如果游戏没有结束，轮到小乌龟，那么小乌龟必须选择一个整数 $i$ 以便 $1 \le i \le m - 1$，将 $a_i$ 设为 $\max(a_i, a_{i + 1})$，并删除 $a_{i + 1}$。
- 如果游戏没有结束，轮到小猪，那么小猪必须选择一个整数 $i$，使得 $1 \le i \le m - 1$，将 $a_i$ 设置为 $\min(a_i, a_{i + 1})$，并删除 $a_{i + 1}$。

小乌龟希望最后**最大** $a_1$ 的值，而小猪希望最后**最小** $a_1$ 的值。如果双方都以最优的方式下棋，求最后 $a_1$ 的值。

### 思路

小猪要最大，小乌龟要最小，那么小猪就会那每次最小的。小乌龟会拿最大的。最后剩下的就是最中间的。如果 $m$ 是奇数最中间就是 $\frac{m+1}{2}$ , 是偶数最中间就是 $\frac{m}{2}+1$ 那就是 $\lfloor \frac{ m}{2} \rfloor +1$ 所以先排序一下在用 $\lfloor \frac{ m}{2} \rfloor +1$ 就行了。

### 代码

```
#include<bits/stdc++.h>
using namespace std;

long long a,b,c[100005];
int main(){
ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>a;
	while(a--){
		cin>>b;
		for(int i=1;i<=b;i++){
			cin>>c[i];
		}
		sort(c+1,c+1+b);
		cout<<c[b/2+1]<<"\n";
	}
return 0;
}
```

[AC 记录](https://codeforces.com/problemset/submission/2003/293463379)

---

## 作者：Program_A2 (赞：2)

由题目不难看出，一个人依次删最小数，另一个人依次删最大数。因此，最后便只剩下大小最中间的数。特别的，当 $n$ 为偶数时，往后再进一位。
```
#define IOI return
#define AK 0
#define ME ;
#include <bits/stdc++.h>
using namespace std;
struct mmm{
	int n;
	vector<int>a;
}b[10001];
int main(){
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>b[i].n;
		for(int l=1;l<=b[i].n;l++){
			int tmp;
			cin>>tmp;
			b[i].a.push_back(tmp);
		}
	}	                //输入各组数据
	for(int i=1;i<=t;i++){
		sort(b[i].a.begin(),b[i].a.end());//这里sort排序不会TLE，还方便
		cout<<b[i].a[b[i].n/2]<<endl;       //输出中间的数
	}
	IOI AK ME
}
```

---

## 作者：__UrFnr__ (赞：2)

**题目大意**：小乌龟和小猪轮流删除序列 $a$ 中的数，小乌龟删除序列 $a$ 的最大值，小猪删除序列 $a$ 的最小值，求序列 $a$ 剩下的数。

**题目思路**：删除最大的数和最小的数，我们先将序列 $a$ 从小到大排序，不断删除当前的最大值和最小值，可以发现最后的结果一定是第 $\lfloor \frac{n}{2}\rfloor +1$ 项，直接输出这一项即可。

代码如下：


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, a[100010]
signed main () {
    cin >> t;
    while (t --) {
    	cin >> n;
    	for (int i = 1; i <= n; i ++) cin >> a[i];
    	sort (a + 1, a + n + 1);
    	cout << a[n / 2 + 1] << '\n';
	}
}
```

---

## 作者：SuyctidohanQ (赞：1)

### 题目分析

呃......大佬们讲的很清楚了。

因为第一个人会优先删除一个最小值，第二个人会优先删除一个最大值，那么所以剩下的就是就只中间值了。最后留下来的一定是第 $⌊ \frac{n}{2} ⌋ + 1$ 小的数。

所以，可以直接使用数组，每一个测试用例都把数存进数组，再直接使用 `sort` 排序就可以了。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
const ll MAXN = 1e5 + 10;
ll T, N, shu[MAXN];
void read () {
	cin >> N;
    for (ll i = 1; i <= N; i ++) cin >> shu[i];
    sort (shu + 1, shu + N + 1);
    cout << shu[N / 2 + 1] << endl;	
}
int main () {
    cin >> T;
    while (T --) read ();
    return 0;
}
```

---

## 作者：TheTrash (赞：1)

### 题意

有两个人轮流删除序列 $a$ 中的数。第一个人每次删除序列中最小的数，第二个人每次删除序列中最大的数，求最后剩下的数。

### 思路

由于两个人轮流删除序列中最小和最大的数，所以最后剩下的一定是序列中的中间值。

### 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
template<class T>void read(T&x){
	x=0;T f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())x=(x<<3)+(x<<1)+c-48;x*=f;
}
template<class T>void write(T x){if(x>9)write(x/10);putchar(x%10+48);}
template<class T>void print(T x,char ed){if(x<0)putchar('-'),x=-x;write(x),putchar(ed);}
int t,n,s[200005];
int main(){
	read(t);
	while(t--){
		read(n);
		for(int i=0;i<n;i++) read(s[i]);
		sort(s,s+n);//排序
		print(s[n/2],'\n');//输出中间值
	}
}
```

[AC记录](https://codeforces.com/contest/2003/submission/290526567)

---

## 作者：wawatime1 (赞：1)

### 题意思路
人删最大的数，那么剩下的不就是中间的数吗？因为先删掉的是最小值，所以剩下的就是大小第 $n \ / \ 2 + 1$ 的数。

最简单的方法：直接排序，输出排序后数组的第 $n\  /\  2 + 1$ 项。
### 代码
```
#include <bits/stdc++.h>
using namespace std;
int t, a[100005], n;
int main () {
	scanf("%d", &t);
	while (t--) {
		scanf ("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf ("%d", &a[i]);
		sort (a + 1, a + 1 + n);
		printf ("%d\n", a[(n + 1) / 2]);
	}
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

由题目不难看出，一个人依次删最小数，另一个人依次删最大数。所以最后是留下第 $⌊\frac{n}{2}⌋ + 1$ 个。

### 代码实现

```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
const ll MAXN = 1e5 + 10;
ll T, N, shu[MAXN];
void read () {
	cin >> N;
    for (ll i = 1; i <= N; i ++) cin >> shu[i];
    sort (shu + 1, shu + N + 1);
    cout << shu[N / 2 + 1] << endl;	
}
int main () {
    cin >> T;
    while (T --) read ();
    return 0;
}
```

---

## 作者：qiuqiu1231 (赞：0)

### 思路
首先，让我们先模拟一组数据，假设输入序列为 $ 3,1,2,2,3 $：


1. Turtle 选择 $ i=4 $，让 $ a_4 = \max(a_4, a_5) = 3 $，去掉 $ a_5 $，序列变成了 $ 3,1,2,3 $。

2. Piggy 选择 $ i=3 $，让 $ a_3 = \min(a_3, a_4) = 2 $，去掉 $ a_4 $，序列变成了 $ 3,1,2 $。

3. Turtle 选择 $ i=2 $，让 $ a_2 = \max(a_2, a_3)=2 $，去掉 $ a_3 $，序列变成了 $ 3,2 $。

4. Piggy 选择 $ i=1 $，让 $ a_1 = \min(a_1, a_2) = 2 $，去掉 $ a_2 $，序列变成了 $ 2 $。

再模拟几组数据，我们不难得出，最后留下来的一定是第 $ \lfloor \frac{n}{2}\rfloor + 1 $ 个，再根据这个结论，便可轻松解决本题。
### 实现
可以直接使用数组，每一个测试用例都把数存进数组，再直接使用 sort 排序就可以了。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int T,n;
    cin>>T;
    for(int i=1;i<=T;i++){
        cin>>n;
        int a[100005];
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        sort(a+1,a+n+1);
        cout<<a[n/2+1]<<endl;
    }
}
```

---

## 作者：mc_xiexie (赞：0)

## 题目描述
Turtle，Piggy 在按顺序玩游戏。给它们一个序列 $ a_1, a_2, \ldots, a_n $。Turtle 和 Piggy 轮流动(Turtle 动第一次，Piggy 动第二次，Turtle 动第三次)。

游戏规则是这样的:

- 让序列的当前长度为 $ m $。如果是 $ m = 1 $，游戏结束。
- 如果游戏没有结束，轮到 Turtle，那么 Turtle 必须选择一个整数 $ i $，例如$ 1 \le i \le m - 1 $，将 $ a_i $ 设置为 $ \max(a_i, a_{i + 1}) $，并删除 $ a_{i + 1} $。
- 如果游戏没有结束，轮到 Piggy，然后 Piggy 必须选择一个整数 $ i $ 如 $ 1 \le i \le m - 1 $，设置 $ a_i $ 为 $ \min(a_i, a_{i + 1}) $，并删除 $ a_{i + 1} $。

Turtle 希望最终使 $ a_1 $ 的值最大化，而 Piggy 希望最终使 $ a_1 $ 的值最小化。如果两个玩家都按最优操作，最后找到 $ a_1 $ 的值。

## 思路
为了最大化最后剩下的数，Turtle 会在他的第 $i$ 轮操作删除序列中第 $i$ 小的数，并且这一定能实现。

同理，Piggy 会在他的第 $i$ 轮操作删除序列中第 $i$ 大的数。

所以最后剩下的就是序列中第 $\lfloor\frac{n}{2}\rfloor + 1$ 小的值。

代码：


```
#include <bits/stdc++.h>
using namespace std;
int n, a[100100],T;
int main() {
	cin>>T;
	while (T--) {
	    cin>>n;
    	for (int i = 1; i <= n; ++i) {
    		cin>>a[i];
    	}
    	sort(a + 1, a + n + 1);
        int mid;
        if(n%2==0){
            mid=n/2+1;
        }
        else{
            mid=(n+1)/2;
        }
    	cout<<a[mid]<<"\n";
	}
	return 0;
}
```

---

## 作者：Defy_HeavenS (赞：0)

# 题意
给定 $n$ 和一个长度为 $n$ 的序列 $a$，两个人轮流玩游戏，~~其实不是人，是乌龟和猪~~。

游戏规则如下：
- 假设当前序列长度为 $m$。若 $m=1$ 则游戏结束。
- 若游戏没有结束，轮到乌龟，选一个位置 $i$（保证 $1\le i\le m-1$），将 $a_i$ 设为 $\max(a_i,a_{i+1})$，并删除 $a_{i+1}$。
- 若游戏没有结束，轮到猪，选一个位置 $i$（保证 $1\le i\le m-1$），将 $a_i$ 设为 $\min(a_i,a_{i+1})$，并删除 $a_{i+1}$。

乌龟希望 $a_1$ 尽可能大，而猪希望 $a_1$ 尽可能小。假定它俩足够聪明，求最后的 $a_1$。

# 思路
模拟样例很重要，先去手动模拟前几个再来（注意看样例解释）。

经过刚才模拟的，我们发现两个~~人~~动物其实是在删元素，那么在删什么样的元素呢？
- 对于乌龟，它希望 $a_1$ 尽可能大，那么它就希望让最小的元素消失，这样就不会让猪用这个最小元素把其他大的元素删除了。
- 对于猪，它希望 $a_1$ 尽可能小，那么它就希望让最大的元素消失，这样就不会让乌龟用这个最大元素把其他小的元素删除了。

有了这样的猜想，可以用这套策略模拟一遍所有的样例了。

经过刚才又一次模拟的，我们可以想想怎么做了，因为每次乌龟会删最小元素、猪会删最大元素，所以最后剩下的是与序列大小在正中间的那个。
- 对于 $n$ 为偶数，因为乌龟先手，所以是 $\frac{n}{2}+1$ 大的元素。
- 对于 $n$ 为奇数，那么就是正中间的元素，所以是 $\frac{n-1}{2}+1$ 大的元素。

所以最终答案就是 $\lfloor \frac{n}{2} \rfloor+1$ 大的元素，那么排个序就行。

# 代码
赛时代码。
```cpp
#include<bits/stdc++.h>
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define pb push_back

using namespace std;
typedef long long LL;
typedef pair<int,int> PII;

const int N=1e5+5;
int n,a[N];
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	cout<<a[n/2+1]<<"\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t=1;cin>>t;
	while(t--) solve();
	return 0;
}
/*

*/
```

---

## 作者：cly312 (赞：0)

第一个人会优先删除一个最小值，第二个人会优先删除一个最大值，那么剩下的就是就只中间值了。所以答案是原序列的第 $\lfloor \frac{x}{2} \rfloor + 1$ 小的数。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int arr[N],n;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>arr[i];
		sort(arr+1,arr+n+1);
		int idx=(1+n)/2;
		if(!(n&1))
			idx+=1;
		cout<<arr[idx]<<endl;
	}
	return 0;
}
```

---

