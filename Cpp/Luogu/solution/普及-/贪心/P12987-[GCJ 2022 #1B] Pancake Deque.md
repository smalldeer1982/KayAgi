# [GCJ 2022 #1B] Pancake Deque

## 题目描述

煎饼通常以堆叠的形式供应，但**无限煎饼屋**勇于变革！该餐厅的新广告噱头是将煎饼以双端队列（deque）的形式供应。

你是餐厅的服务员，你的工作是从双端队列中供应所有煎饼。顾客会依次到来，每位顾客获得一个煎饼。你必须为每位顾客供应当前双端队列的最左端或最右端的煎饼，选择权在你手中。当一个煎饼被供应后，它会从队列中消失，露出相邻的煎饼。或者，当只剩一个煎饼时，你只能供应它，此时你的工作就完成了！

![](https://cdn.luogu.com.cn/upload/image_hosting/jn04ll9k.png)

每个煎饼有一个美味值。由于顾客无法选择自己获得的煎饼，只有当一个煎饼的美味值**不低于**之前所有顾客获得的煎饼的美味值时，该顾客才需要为其煎饼付费。（第一位顾客总是需要付费，因为此时没有之前的顾客。）

如果你以最大化付费顾客数量的顺序供应煎饼，有多少顾客会为其煎饼付费？

## 说明/提示

**样例解释**

在样例 #1 中，有两种供应煎饼的顺序。如果先供应美味值为 5 的煎饼，则只有该顾客付费；如果先供应美味值为 1 的煎饼，则两位顾客都会付费。

样例 #2 对应题目描述中的图片。以下是可能的供应顺序（按美味值），下划线的煎饼表示顾客需要付费：
- $\underline{1}, 4, 2, 3$
- $\underline{1}, 4, 3, 2$
- $\underline{1}, \underline{3}, 4, 2$
- $\underline{1}, \underline{3}, 2, \underline{4}$
- $\underline{3}, 1, \underline{4}, 2$
- $\underline{3}, 1, 2, \underline{4}$
- $\underline{3}, 2, 1, \underline{4}$
- $\underline{3}, 2, \underline{4}, 1$

可以看到，某些顺序下会有 3 个煎饼被付费，但没有一种顺序能让所有 4 个煎饼都付费。

在样例 #3 中，无论以何种顺序供应，所有煎饼都会被付费。

在样例 #4 中，无论先供应哪个煎饼，中间的两个煎饼都不会被付费。最佳策略是先供应美味值为 7 的煎饼，再供应美味值为 1000000 的煎饼。

**数据范围**

- $1 \leq T \leq 100$。
- $1 \leq D_i \leq 10^6$（对所有 $i$ 成立）。

**测试集 1（7 分，可见判定）**

- $2 \leq N \leq 20$。

**测试集 2（8 分，可见判定）**

- $2 \leq N \leq 100$。

**测试集 3（10 分，隐藏判定）**

- $2 \leq N \leq 10^5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
2
1 5
4
1 4 2 3
5
10 10 10 10 10
4
7 1 3 1000000```

### 输出

```
Case #1: 2
Case #2: 3
Case #3: 5
Case #4: 2```

# 题解

## 作者：__VN (赞：3)

# P12987 [GCJ 2022 #1B] Pancake Deque
[题目传送门 ](https://www.luogu.com.cn/problem/P12987) [题解代码通过记录](https://www.luogu.com.cn/record/221801411)


---


## 思路
先使队列两端较小值出列，可使美味值最大值增长更缓慢。

这样后续煎饼更容易满足支付条件（只需 $ \geq $ 较小值而非较大值），增加后续付费机会。
## 注意
当一个煎饼的美味值**不低于**之前**所有**煎饼的美味值时，该顾客才为其煎饼付费。

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    cin>>T;
    for(int i=1;i<=T;i++){
    	int n;
    	int last=0;			//之前所有顾客获得的煎饼的美味值最大值 
    	int sum=0;			//付费顾客数量
    	list<int> d;		//煎饼！ 
    	cin>>n;
    	while(n--){			//输入
    		int x;			
    		cin>>x;
    		d.push_back(x);
		}
    	while(!d.empty()){
    		if(d.front()>d.back()){						//判断队首和队尾煎饼的美味值	
    			if(d.back()>=last)last=d.back(),sum++;	//判断是否不低于之前所有顾客获得的煎饼的美味值
    			d.pop_back();							//出队 
			}else{										//同上 
				if(d.front()>=last)last=d.front(),sum++;
    			d.pop_front();
			}
		}
		printf("Case #%d: %d\n",i,sum);
	}
}
```

---

## 作者：Gongyujie123 (赞：2)

## [P12987 [GCJ 2022 #1B] Pancake Deque](https://www.luogu.com.cn/problem/P12987) 题解
### 1. 题目大意
给定一个双端队列，每次在最左端或最右端删除一个数，
求有多少个满足条件的数。条件：
- 每次删除的这个数不小于之前删除的所有数。
### 2. 思路分析
很容易想到，这道题是**贪心**。那我们该如何贪呢？

稍加思考后，我们可以发现每次应该删除两端最小的那个数。为什么呢？

我们可以假设这个队列为 ${1, 3, 2, 4}$。

如果我们每次删除两端最小的那个数，可以得到答案为 $3$。但如果我们每次不删除最小的那个数（如 $1$ 和 $4$，我们删除 $4$，剩下的三个数就都不满足条件），答案就为 $1$。所以，每次应该删除两端最小的那个数。

那我们该如何判断每次删除的这个数不小于之前删除的所有数呢？

我们可以定义一个变量维护之前删除的所有数的最大值，我们就可以直接判断每次删除的这个数是否不小于这个变量。

### 3. AC 代码

[AC 记录](https://www.luogu.com.cn/record/221731040)，最慢点：910 ms。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100005];
signed main(){
	int t;
	cin >> t;
	int t1 = t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
		}
		int maxx = 0, ans = 0;
		for (int i = 0, j = n - 1; i <= j; ) {
			if (a[i] < a[j]) {
				if (a[i] >= maxx) {
					ans++;
					maxx = max(maxx, a[i]);
				}
				i++;
			} else if (a[i] > a[j]) {
				if (a[j] >= maxx) {
					ans++;
					maxx = max(maxx, a[j]);
				}
				j--;
			} else {
				if (a[i] >= maxx) {
					ans += (i == j ? 1 : 2);
					maxx = max(maxx, a[i]);
				}
				i++;
				j--;
			}
		}
		printf("Case #%lld: %lld\n", t1 - t, ans);
	}
	return 0;
}
```

---

## 作者：_hud (赞：1)

# 题解：[P12987 \[GCJ 2022 #1B\] Pancake Deque](https://luogu.com.cn/problem/P12987)

## 思路

贪心。

由题意不难发现，付费顾客序列必须满足单调不减性。因此很容易想到的贪心思路是，每次优先选择双端队列两端美味值较小的煎饼供应，这样可以尽量使以后顾客煎饼的美味值不低于之前所有顾客获得的煎饼的美味值，从而对答案造成贡献。

然后按照题意模拟即可。具体可以看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
// a 为双端队列 hh 为队头 tt 为队尾
int a[100010], hh, tt, ans, maxn, tmp;
signed main() {
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
    int T; cin >> T;
    for(int cc = 1; cc <= T; ++cc) {
        cin >> tt; hh = maxn = 1; ans = 0;
        for(int i = 1; i <= tt; ++i) cin >> a[i];
        while(hh <= tt) { // 队列不为空时循环
            if(a[hh] < a[tt]) tmp = a[hh++];
            else tmp = a[tt--];
            if(tmp >= maxn) maxn = tmp, ++ans; // 造成了贡献，更新最值
        }
        cout << "Case #" << cc << ": " << ans << '\n';
    }
    return 0;
}
```

---

## 作者：chenyizhen (赞：1)

### 题目：

在数组两端选数，使后选的数尽量多的大于等于之前选出的数。

### 思路：

形式化题意就是：在数组左右两端挑选**最长的不下降子序列**，序列的长度即为我们所要求的 $ans$（即最多付费顾客个数，~~我开始为资本做局了？~~）。

那我们根据贪心的思想就可以想到**先选出左右两端小的数**，毕竟大的数不会被小的数所覆盖，反之则不然，这样我们就可尽可能多的选出付费顾客个数。

### 实现：

- 通过 C++ 自带的双端队列或自己通过数组模拟双端队列来模拟挑选过程。
- 在挑选过程中记录已挑选的最大值以便于今后的比较。
- 按照题目输出。

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=6e5+5;
inline void read(int &a){
	char ch;int f=1,k=0;ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){k=k*10+ch-'0';ch=getchar();}
	a=k*f;
}
int d[N],cnt=0,n,T;
signed main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);cout.tie(0);	
	read(T);
	while(T--){
		read(n);
		for(int i=1;i<=n;i++) read(d[i]);
		int head=1,tail=n,ans=0,maxn=0;
		while(head<=tail){
			if(d[tail]>d[head]){
				ans+=d[head]>=maxn;
				maxn=max(maxn,d[head]);
				head++;
			}else{
				ans+=d[tail]>=maxn;
				maxn=max(maxn,d[tail]);
				tail--;
			}
		}
		printf("Case #%lld: %lld\n",++cnt,ans);
	}
	return 0;
}
```

在这里我选用自己模拟双端队列，因为自带的 `deque` 效率较低，在这道题中处理时间的差别也很明显。~~我目前还是最优解呢。~~

---

## 作者：bayiran (赞：1)

### P12987 [GCJ 2022 #1B] Pancake Deque 题解

#### 题意分析

可以把题目形式化为：有一个双向队列，可以从左端或右端删除元素，并且只有当这个元素大于等于所有之前被删除元素时才可以被删除，问最多可以删除多少个元素。

#### 解决策略

1. 使用两个指针分别指向队首和队尾。
2. 每次比较开头和结尾的值，选择较小的一个。
3. 同时维护一个当前已经删除的值中的最大值。
4. 如果当前选择的值大于等于已经删除的最大值，则删除数量加一，并更新最大删除值。
5. 删除选择的值，并移动相应指针。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int mmax(vector<int> pan){
    int n = pan.size();
    int left = 0, right = n-1;
    int mis = -1;
    int paid = 0;
    while(left <= right){
        int lv = pan[left];
        int rv = pan[right];
        int maxv = min(lv,rv);
        if(maxv >= mis) {
            paid ++;
            mis = maxv;
        }
        if(lv == maxv) {
            left++;
        }
        else{
            right--;
        }
    }
    return paid;
}

int main() {
    int T;
    cin>>T;
    for(int t=1;t<=T;t++){
        int n;
        cin>>n;
        vector<int> pan(n);
        for(int i=0;i<n;i++){
            cin>>pan[i];
        }
        int res = mmax(pan);
        cout<<"Case #"<<t<<": "<<res<<endl;
    }

    return 0;
}

```
时间复杂度 $O(Tn)$。

---

## 作者：_WCW_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12987)
## 解题思路
这道题很明显是一道贪心题，要求这一轮选择的数只有不低于前面所有选择的数，答案加一，那么最优的贪心策略必然是每轮选队列中头和队列尾中较小的数，更方便后续的选择（因为要求这一轮选择的数必须前面的数大，那么前面的数越小越好选）。之后用 ```deque``` 实现双端队列并进行上面的贪心策略即可。
## [AC](https://www.luogu.com.cn/record/221882482) 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;//这两个变量均为题中意思
int main()
{
    scanf("%d",&t);//读入t
    for(int i=1;i<=t;i++)//循环t次
    {
        int ans=0;//初始化这轮结果为0
        scanf("%d",&n);//读入n
        deque<int> q;//双端队列q
        for(int j=1;j<=n;j++)//循环n次
        {
            int d;//每轮输入数据
            scanf("%d",&d);//读入
            q.push_back(d);//将数据放入双端队列中
        }
        int prev=INT_MIN;//prev变量用于记录上一轮选择的数，初始化为INT_MIN
        while(!q.empty())//队列不为空就循环找数
        {
            if(q.front()<=q.back())//如果队列头的数更小
            {
                if(q.front()>=prev)//检查是否满足大于前一个数的条件
                {
                    prev=q.front();//更新prev变量
                    ans++;//答案加一
                }
                q.pop_front();//弹出队头元素
            }
            else//否则选择队列尾的元素
            {
                if(q.back()>=prev)//检查是否满足大于前一个数的条件
                {   prev=q.back();//更新prev变量
                    ans++;//答案加一
                }
                q.pop_back();//弹出队尾元素
            }
        }
        printf("Case #%d: %d\n",i,ans);//输出结果
    }

    return 0;
}
```

---

## 作者：Andy0121 (赞：1)

# P12987 题解
## 题意
给出一个双端队列，要求出队的数单调不降，求最大可出队数
## 思路
考虑贪心。

因为要单调不降且尽可能多出队，所以要让每次出队的尽可能小。
### 证明：
设左边比右边小，但最优解是先出右边。则可以在出右边之前先把左边出队，不影响后面结果，与假设矛盾。

所以记录当前的最大值，把左右之中最小不小于当前最大值的出队，更新最大值。
## AC code
不要复制题解
```cpp
#include<bits/stdc++.h>
#define just return
#define do 0 
#define it ;
using namespace std;
int a[100005];
int main(){
	int n;
	cin >> n;
	for(int i = 0;i < n;i++){
		int m;
		cin >> m;
		for(int j = 0;j < m;j++){
			cin >> a[j];
		}
		int l = 0,r = m-1,max_now = -1,cnt = 0;
		while(l <= r){
            if(a[l] <= a[r]){
                if(a[l] >= max_now){
                    max_now = a[l];
                    cnt++;
                }
                l++;
            }else{
                if(a[r] >= max_now){
                    max_now = a[r];
                    cnt++;
                }
                r--;
            }
        }
		cout << "Case #" << i+1 << ": " << cnt << '\n';
	}
	just do it
}
```

---

## 作者：yyz0526 (赞：0)

## 题目大意：
以**双端队列**（[`deque` 讲解](https://oi-wiki.org/lang/csl/container)）的方式供应煎饼，每个煎饼有一个美味值，只有当一个煎饼的美味值**不低于**之前所有顾客获得的煎饼的美味值时，该顾客才需要为其煎饼付费。求**最大化**付费顾客的数量。

## 思路：
想要最大化付费顾客数量，每一次取的煎饼的美味值就需要最小，取队首和队尾的**最小值**，然后与前几次选择的煎饼的**最大美味值**进行比较，如果不小于，那么就要付费。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
deque<int> d;
int main(){
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;i++){
		while(!d.empty()){ // 清空队列。
			d.pop_back();
		}
		int n,sum=0;
		int maxx=0; // 当前最大美味值。
		scanf("%d",&n);
		for(int j=0;j<n;j++){
			int x;
			scanf("%d",&x);
			d.push_back(x);
		}
		while(!d.empty()){
			int f=d.front();
			int b=d.back();
			if(f<b){ // 队首小。
				if(maxx<=f){
					maxx=f;
					sum++;
				}
				d.pop_front();
			}
			else{ // 队尾小。
				if(maxx<=b){
					maxx=b;
					sum++;
				}
				d.pop_back();
			}
		}
		printf("Case #%d: %d\n",i,sum);
	}
	return 0;
}
```

---

## 作者：Clouds_dream (赞：0)

### 前置知识

[贪心——oi-wiki](https://oi-wiki.org/basic/greedy/)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P12987)

### 思路
既然是贪心，那么我们应该如何贪呢？  
我们可以用一个双端队列 $dq$ 来表示煎饼序列，用 $maxn$ 来表示当前美味值，用 $xuan$ 表示选择的元素值（$l$ 或 $r$），用 $ans$ 表示答案。每次选择两端中较小且满足不小于当前最大美味值（$maxn$）的一个，即 $l \le r$ 时，$xuan$ 等于 $l$，否则等于 $r$，这样能保证后续有更多的选择（因为留了一个较大的在另一端，后续可能取到）。如果两端都小于当前最大美味值，那么就不能再取了（终止条件）。  

### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main()
{
	int q;
	cin>>q;
	for(int t=1;t<=q;t++){
		int n;
		cin>>n;
		deque<int>dq;
		for(int i=1;i<=n;i++){
			int x;
			cin>>x;
			dq.push_back(x);
		}
		int maxn=0,ans=0;
		while(!dq.empty()){
			int l=dq.front(),r=dq.back();
			int xuan;
			if(l<=r){
				xuan=l;
				dq.pop_front();
			}
			else{
				xuan=r;
				dq.pop_back();
			}
			if(xuan>=maxn){
				ans++;
				maxn=xuan;
			}
		}
		cout<<"Case #"<<t<<": "<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：_BYTE_ (赞：0)

# [P12987 [GCJ 2022 #1B] Pancake Deque](https://www.luogu.com.cn/problem/P12987) 题解

## 思路
运用贪心即可通过。

为了避免最大值的快速增长，使更多的顾客为煎饼付费，取队列两端较小的值出列。

然后与先前记录的最大值比较，进行更新操作。

**注**：当新煎饼的**大于等于**（而非**大于**）先前所有煎饼的最大值时，顾客就会为其付费。
## AC代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,ans=0;
deque<int> q;
int main(){
	cin>>T;
	for(int i=1;i<=T;i++){
		cin>>n;
		int x,Max=-1;
		for(int j=1;j<=n;j++){
			cin>>x;
			q.push_back(x);
		}
		while(!q.empty()){
			if(q.front()<q.back()){
				if(q.front()>=Max)
					ans++,Max=q.front();
				q.pop_front(); 
			}else{
				if(q.back()>=Max)
					ans++,Max=q.back();
				q.pop_back(); 
			}
		}
		cout<<"Case #"<<i<<": "<<ans<<endl;
		ans=0;
	}
}
```
[记录](https://www.luogu.com.cn/record/222069580)

---

