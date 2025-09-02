# [GCJ 2016 #1C] Senate Evacuation

## 题目描述

参议院会议厅里起了一场小火，必须进行疏散！

会议厅里有若干参议员，每位参议员都属于 $\mathbf{N}$ 个政党中的某一个。这些政党的名称分别为英语字母表前 $\mathbf{N}$ 个大写字母。

紧急出口足够宽敞，每一步疏散时你可以选择移除一名或两名参议员。

参议院的规则规定，即使在疏散过程中，会议厅里的参议员也可以随时对任何议案进行投票！因此，疏散必须以一种方式进行，保证任何时刻都不会有某个政党拥有绝对多数。也就是说，在任何一次疏散操作之后，会议厅中都不能出现某个政党成员人数超过总人数一半的情况。

你能制定一个疏散方案吗？参议院全靠你了！

## 说明/提示

**样例解释**

样例输出展示的是一组可能的答案，其他答案也可能是正确的。

在第 1 组中，A 和 B 两个政党各有两名参议员。如果每次各移除一人，始终保持完美平衡，直到全部疏散。

第 2 组操作如下：

- 初始：3 名 A，2 名 B，2 名 C。
- 疏散 AA。剩余：1 名 A，2 名 B，2 名 C。
- 疏散 BC。剩余：1 名 A，1 名 B，1 名 C。
- 疏散 C。剩余：1 名 A，1 名 B。
- 疏散 AB。全部疏散完成！

注意，不能以 BC 开始疏散，否则剩下 3 名 A，1 名 B，1 名 C，A 党将拥有绝对多数（3/5 = 60%）。

对于第 3 组，CC AB 也是一个合法答案，C C AB 也是合法的，尽管需要三步而不是两步。

**限制条件**

- $1 \leqslant \mathbf{T} \leqslant 50$。
- 在疏散开始前，没有任何政党拥有绝对多数。
- 对所有 $i$，$1 \leqslant \mathbf{P}_i \leqslant 1000$。

**小数据集（8 分，测试集 1 - 可见）**

- $2 \leqslant \mathbf{N} \leqslant 3$。
- 所有 $\mathbf{P}_i$ 之和 $\leqslant 9$。

**大数据集（10 分，测试集 2 - 隐藏）**

- $2 \leqslant \mathbf{N} \leqslant 26$。
- 所有 $\mathbf{P}_i$ 之和 $\leqslant 1000$。

翻译由 GPT4.1 完成。

## 样例 #1

### 输入

```
4
2
2 2
3
3 2 2
3
1 1 2
3
2 3 1```

### 输出

```
Case #1: AB BA
Case #2: AA BC C BA
Case #3: C C AB
Case #4: BA BB CA```

# 题解

## 作者：qkj_qwq (赞：3)

## 解题思路
其实不用这么难，又不用求最优解，而且保证有解。

我们依次把当前政党人数最多的政党移除一人。当然，也需要特判：
- 当总政党数刚好为 $2$ 时，由于保证至少存在一种合法的疏散方案，所以给出的数据肯定是两个政党人数相等的。这时只需要输出 `AB AB AB ...` 即可。
- 当只剩下最后两个人时（可以证明最后两个人不是同一政党的），两个人需要一起输出。

其它情况就一个一个输出。其它情况因为当总政党数 $\ge3$，所以即使最极端的情况（`n n+1 1`），也有第三个政党来帮你控制人数在一半以内。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[36];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++)
	{
		cout<<"Case #"<<tt<<": ";
		int n,maxn=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i],maxn=max(maxn,a[i]);
		for(int i=maxn;i>=1;i--)
			for(int j=1;j<=n;j++)
				if(a[j]>=i)//按人数大小来输出
				{
					cout<<char('A'+j-1);
					if(!(j==1&&n==2)&&!(i==1&&j==n-1))cout<<' ';
					//   特判情况 1       特判情况 2
				}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：chinazhanghaoxun (赞：1)

## 题意分析

这道题使用贪心，每次都优先疏散当前人数最多的政党，这样可以尽量避免某个党派形成绝对多数。因为可以疏散一个或者两个议员，我们不妨优先尝试疏散两个议员。如果疏散两个议员会导致失败，则回溯第二个人，只疏散一人。因为题目保证存在一种满足题意的疏散方式，所以我们这样的操作是可以得到一组答案的。

## 实现方式

由于每次都需要取出人数最多的党，可以使用优先队列维护人数最多的政党，每一个元素存储党派的人数和代号。实现过程如下：

- 每次从堆中取出人数最多的党，疏散两个人
- 模拟疏散两个人，更新人数
- 检查疏散后是否依旧合法，循环每个党派
- 若合法，就疏散这两个人
- 若不合法，回溯第二人，只疏散第一个人

## 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;

typedef pair<int,int> party;
priority_queue<party> q;
int a[30],T,n;

int main(){
	cin>>T;
	for(int t=1;t<=T;t++){
		cin>>n;
		int sum=0;
		for(int i=0;i<n;i++){
			cin>>a[i];
			q.push({a[i],i});
			sum+=a[i]; //记录总人数
		}
		
		cout<<"Case #"<<t<<": ";
		
		while(sum){
			//尝试疏散一人 
			auto [x1,i1]=q.top();
			q.pop();
			x1--;
			sum--;
			string step=""; //记录疏散过程 
			step+='A'+i1;
			
			if(!q.empty()){ //还有其他党派 
				auto[x2,i2]=q.top();
				q.pop();
				x2--;
				sum--;
				//模拟疏散这两人 
				a[i1]=x1;
				a[i2]=x2;
				bool valid=1;
				for(int i=0;i<n;i++)
					if(a[i]>sum/2) //有过半的党派 
						valid=0;
						
				if(valid){
					step+='A'+i2;
					if(x2)
						q.push({x2,i2});
				}else{
					//回溯第二人 
					x2++;
					sum++;
					a[i2]++;
					q.push({x2,i2});
				}
			}
			
			//疏散第一人 
			a[i1]=x1;
			if(x1)
				q.push({x1,i1});
			cout<<step<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：xk2013 (赞：1)

题目传送门：[P13195 [GCJ 2016 #1C] Senate Evacuation](/problem/P13195)

## 前置知识
- 贪心。

## 题意简述
有一堆参议员分别属于 $n$ 个政党，现在要疏散，一次可以赶出去一个或者两个人，赶的时候任何一个政党不能有超过半数人，输出任意一种方案。

## 解题思路
贪心就完了。每次把人最多的政党赶出去一个人，考虑最极端的情况：两个政党各有 $x$ 个人，赶出去一个人另一个政党就有超过半数人了，所以如果赶出去后不符合条件那就再把人最多的政党赶出去一个人就行了，到这里就可以了，因为题目保证有解。

## 完整代码
看完上面再看这儿，不能只看这儿，更不能 Copy！
```cpp
// Problem: P13195 [GCJ 2016 #1C] Senate Evacuation
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P13195
// Memory Limit: 1024 MB
// Time Limit: 7500 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <cstdio>

constexpr int N = 30;
int T, n, max, sum, a[N];

int main(void)
{
	scanf("%d", &T);
	
	for (int t = 1; t <= T; t++)
	{
		max = sum = 0;
		scanf("%d", &n);
		printf("Case #%d: ", t); // 这个别忘记
		
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
			sum += a[i]; // 统计和方便判断
			
			if (a[i] > a[max]) max = i; // 找最大值
		}
		
		while (sum > 0) // 人没赶完
		{
			a[max]--; // 赶了一个
			sum--; // 这个别忘
			putchar('A' + max - 1); // 输出
			
			for (int i = 1; i <= n; i++)
			{
				if (a[i] > a[max]) max = i; // 求最大值
			}
			
			if (sum > 0 && a[max] * 2 <= sum) putchar(' '); // 如果符合条件就快进到下一次 否则不满足条件的话可以直接接上
		}
		
		putchar('\n');
	}
	
	#define _ 0
	return ~~(0^_^0);
	#undef _
}

```
----------------------
这是本五升六蒟蒻小学生的第 28 篇题解，不喜可喷，但求你不要喷太猛了哦~

## 更新日志
- 2025/07/20：初版。

---

## 作者：Nostopathy (赞：1)

# Solution

考虑贪心。每次操作都在人数最多的政党中移出一人，若此时出现了绝对多数，则又在此时人数最多的政党中选择一人加入这次操作，直到全部完成。

若一次操作完成后仍然有绝对多数，则问题无解。但本题保证有解，所以我撤回刚才的话。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define pb push_back
#define rep(a, b, c, d) for(int a=b; a<=c; a+=d)
const int N = 30;
int n, a[N];
int max_num() {
	int m = 0;
	for (int i = 1; i <= n; ++ i)
		m = max(m, a[i]);
	return m;
}
int max_pos() {
	int m = 0, p = 0;
	for (int i = 1; i <= n; ++ i)
		if (a[i] > m)
			m = a[i], p = i;
	return p;
}
signed main() {
	int t;
	scanf("%lld", &t);
	rep(c, 1, t, 1) {
		int sum = 0;
		scanf("%lld", &n);
		rep(i, 1, n, 1)
			scanf("%lld", &a[i]), sum += a[i];
		printf("Case #%lld: ", c);
		while(sum) {
			int p = max_pos();
			-- a[p], -- sum;
			putchar('A' - 1 + p);
			if(sum && (max_num() << 1) <= sum)
				putchar(' ');
		}
		puts("");
	}
	return 0;
}
```

谢谢观看。

~~没有求关的题解不是好题解。~~

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13195)

# 题目分析

设当前人数为 $t$。

首先来考虑 $t>2$ 的情况。此时可以每次从人数最多的政党中疏散一人。证明：

疏散前一共有 $t$ 人，假设疏散前没有绝对多数，从当前人数最多的政党中疏散掉一个人后，却出现了绝对多数。设原来人数最多的政党有 $m$ 个人，则其他政党最多只有 $m$ 个人。疏散后该政党剩下 $m-1$ 个人，则此时的绝对多数只能出现在人数为 $m$ 的政党中（因为疏散后人数最多的政党最多 $m$ 个人，即上述的“其他政党”）。由于出现了绝对多数，我们有 $\frac{m}{t-1}>\frac{1}{2}$，变形后有 $2m>t-1$，由此可推出 $m>\frac{t}{2}$，因此疏散前存在绝对多数，与条件矛盾。因为初始状态没有绝对多数，因此条件成立，即该方案可行。

上述步骤可以使用优先队列，队首元素即为人数最多的政党。

下面考虑 $n=2$ 的情况。显然，此时两个政党人数相等，设两个政党分别为 A 和 B，则不断输出 ```AB``` 即可。

若 $n=1$，不断输出唯一一个政党的字母即可。

# 代码


```cpp
#include<bits/stdc++.h>
#define N 30
using namespace std;
struct pa{
	int num;
	char na;
}p[N];
bool operator <(pa x,pa y){
	return x.num<y.num;
}
priority_queue<pa> q;
int main(){
	int t;
	cin>>t;
	for(int o=1;o<=t;o++){
		cout<<"Case #"<<o<<": ";
		int n;
		cin>>n;
		while(!q.empty()){
			q.pop();
		}
		for(int i=1;i<=n;i++){
			cin>>p[i].num;
			p[i].na='A'+i-1;
			q.push(p[i]);
		}
		while(!q.empty()){
			int yes=1;
			if(q.size()==2){
				pa s=q.top();
				q.pop();
				pa t=q.top();
				q.pop();
				for(int j=1;j<=s.num;j++){
					cout<<s.na<<t.na<<' ';
				}
				yes=0;
			}
			else if(q.size()==1){
				pa s=q.top();
				q.pop();
				for(int j=1;j<=s.num;j++){
					cout<<s.na<<' ';
				}
				yes=0;
			}
			if(!yes){
				break;
			}
			pa nowp=q.top();
			q.pop();
			cout<<nowp.na<<' ';
			nowp.num--;
			if(nowp.num){
				q.push(nowp);
			} 
		}
		cout<<endl;
	}
	return 0;
} 
```

---

