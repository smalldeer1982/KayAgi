# Driving Test

## 题目描述

Polycarp刚尝试通过驾驶考试。他跑过直道，有四种类型的标识牌。

1、**速度限制**：此符号带有一个正整数，表示汽车的最大速度（取消此类型上一个符号的动作）;

2、**允许超车**：这个标志意味着一些车遇到它后，它可以超过任何其他车（这句话对着样例意会一下）;

3、**无速度限制**：此标志取消限速（如果有的话）（汽车可以在此标志后以任意速度移动 ;

4、**取消超车允许**：一些车在这个标志后不能超过任何其他车。

Polycarp通过了这些标志，每个新标志都取消了之前所有标志（速度限制/超车）的动作。

有可能两个或多个“没有超车允许”的标志一个接一个地出现，它们之间没有“超车允许”标志。这个说明适用于“无速度限制”和“超车允许”标志。

在乘坐开始时允许超车并且没有速度限制。

现在按时间顺序给出了一系列事件 - 在乘坐过程中发生在Polycarp的事件。有以下类型的事件：

Polycarp将他的汽车速度改为指定（用一个正整数表示）
;
Polycarp的车超越了另一辆车;

Polycarp的汽车经过了“限速”标志（此标志带有正整数）;

Polycarp的汽车经过“超车允许”标志;

Polycarp的汽车经过了“无限速”;

Polycarp的赛车经过了“不允许超车”;

保证按时间顺序的第一个事件是类型1的事件（Polycarp将他的汽车的速度改为指定的）。

在考试结束后，Polycarp可以通过告诉驾驶教练他没有注意到某些迹象来证明他的违规行为是正当的。

Polycarp现在要证明他的违规行为是正当的，那么他最少要说的自己没有注意到的标识数量是多少？

## 样例 #1

### 输入

```
11
1 100
3 70
4
2
3 120
5
3 120
6
1 150
4
3 300
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
1 100
3 200
2
4
5
```

### 输出

```
0
```

## 样例 #3

### 输入

```
7
1 20
2
6
4
6
6
2
```

### 输出

```
2
```

# 题解

## 作者：_edge_ (赞：2)

还算比较良心的模拟题，至少没有一大堆细节去修改。

我们先来梳理一下题目，题目的意思是说，无速度限制会将之前的速度限制全部取消掉，速度限制会取消速度限制。

我们发现这个超车比较好处理，只要记录当前经过了几个超车的标志，注意允许超车的时候，将这个变量清空。

如果在不允许超车的情况下超车了，也把变量清空，将答案累加。

但是我们发现这个速度就非常难搞，它具有不同的限制。

我们可以搞一个栈来维护，当前经过的速度限制，如果这个速度限制比较大的话，它会覆盖掉，就是说如果之前出现过比较小的速度限制，不会违反规则。

注意一下数组大小即可。

如有问题还请指出。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=3e5+5;
int n,ans,s[INF],r;
signed main()
{
    scanf("%d",&n);
    int fl=1,su=0,pp=0,pp1=0,sum2=0,lim=0;
    for (int i=1;i<=n;i++) {
        int op=0;
        scanf("%d",&op);
        if (op==1) {
            scanf("%d",&su);
            while (r && s[r]<su) r--,ans++;
        }
        else if (op==2) {
            if (fl) continue;
            if (pp1==0) pp1=1,ans+=sum2,sum2=0;
        }
        else if (op==3) {
            scanf("%d",&lim);
            r=0;
            s[++r]=lim;
            while (r && s[r]<su) r--,ans++;
        }
        else if (op==4) fl=1,sum2=0;
        else if (op==5) r=0;
        else fl=0,pp1=0,sum2++;
    }
    cout<<ans<<"\n";
    return 0;
}
```


---

## 作者：skyskyCCC (赞：1)

## 前言。
小型模拟，但是很难，单指理解题意。
## 分析。
一共有 $6$ 种情况，所以分开模拟即可。

首先需要明确，因为题目中明确规定在乘坐开始时允许超车并且没有速度限制，所以我们将最大速度调到最大。然后我们依次分析每一个操作。然后我们开一个栈，用来存储目前我们已经记录的所有的限速标志。

首先对于操作一：将他的汽车速度改为指定速度，此时我们要对比从出发到现在所有的限速标志，如果超速则则加一个违法记录，一直遍历到第一个不超速就停止。这是因为我们只关心前面的记录，后面要求多少的速度都没有关系因为我们还没有遇见这个限速牌。所以我们只需要关心我们已经经过的限速牌即可。

对于操作二：车超越了另一辆车。如果此时是不容许超车，那么此前经过了 $n$ 个不许超车的牌，就有 $n$ 次违规，所以加上这 $n$ 个牌的个数即可。注意到 $n$ 可以等于 $0$ 所以如果此前没有这个牌，也没有关系，因为不会被统计。但是注意到遇到可以超车，则累计的全部被超，所以需要清零。

对于操作三：汽车经过了“限速”标志，则需要判断一下。如果当前超速，则要把违规记录加上一个，因为我们要编造没有看见的牌，所以不需要将此前的限速牌放入栈中了。否则，加到栈中。

对于操作四：汽车经过“超车允许”标志，那么清空统计不容许超车牌数量的那个变量即可。

对于操作五：汽车经过了“无限速”地区，那么我们就可以无限度地开到最大值，所以重新初始化到最大数，然后此前的限速都没有用了，所以都弹出来即可。

对于操作六：经过了“不容许超车”区，那么统计一下即可。

代码如下，仅供参考：
```
#include<iostream>
#include<stack>
using namespace std;
int n,t,new_s,maxx_s=0x3f3f3f3f;
int sum1,sum2;
stack<int> st;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>t;
		if(t==1){
			cin>>new_s;
			while(st.empty()==0&&new_s>st.top()){
				st.pop();
				sum1++;
			}
			//cout<<sum1<<" 1 \n";
		}
		else if(t==2){
			sum1+=sum2;
			sum2=0;
			//cout<<sum1<<" "<<sum2<<" 2 \n";
		}
		else if(t==3){
			cin>>maxx_s;
			if (maxx_s<new_s) sum1++;
			else st.push(maxx_s);
			//print();
		}
		else if(t==4){
			sum2=0;
		}
		else if(t==5){
			maxx_s=0x3f3f3f3f;
			while(st.empty()==0) st.pop();
			//print();
		}
		else if(t==6){
			sum2++;
			//cout<<sum1<<" "<<sum2<<" 6 \n";
		}
	}
	cout<<sum1<<"\n";
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：first_fan (赞：1)

一道两秒钟限时的模拟题。

考虑怎么记录题设所给条件：

* 速度，超车提示个数用单整形存储

* 限速使用栈存储（方便计算违规次数）

那么我们在改变速度之后、超过超车提示时这两种情况下可能需要累加失误次数。

而在遇到取消限制指令时把限速栈清空、超车提示数清零即可。

```cpp
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;

int read()
{
	int num=0;
	int flg=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		{
			flg=-1;
		}
		c=getchar();
	}
	while(isdigit(c))
	{
		num=(num<<1)+(num<<3)+(c^48);
		c=getchar();
	}
	return num*flg;
}

stack<ll>s;

int main()
{
	int n=read();
	int speed=0;
	int cnt=0;
	int over=0;
	int lim=0;
	while(n--)
	{
		int opt=read();
		switch(opt)
		{
			case 1:
			{
				speed=read();
				break;
			}//改变速度
			case 2:
			{
				cnt+=over;
				over=0;
				break;
			}//超车
			case 3:
			{
				lim=read();
				s.push(lim);
				break;
			}//限速
			case 4:
			{
				over=0;
				break;
			}//允许超车
			case 5:
			{
				stack<ll>Void;
				swap(Void,s);
				break;
			}//取消限速
			default://6
			{
				over++;
				break;
			}//禁止超车
		}
		while(s.size()&&s.top()<speed)
		{
			s.pop();
			cnt++;
		}
	}
	return 0&printf("%d",cnt);
}
```

---

## 作者：DANIEL_x_ (赞：0)

## 思路分析：
按时间顺序处理所有的事件，应该保持限速标志的堆积和不允许超车标志的数量

1. 如果我们遇到限速标志，我们把它的极限推到堆栈中。

2. 不允许超车标志，代表增加 $cnt$。

3. 不限速代表清除堆栈。

4. 允许超车代表把 $cnt$ 分配为零。

在每个事件之后，我们应该检查我们的速度是否正常。当堆栈顶部的标志值小于当前速度时，弹出它并增加答案。如果我们超过了某人，我们将 $cnt$ 加到答案中，并将 $cnt$ 赋值为零。

## code:
```cpp
#include <bits/stdc++.h>
using namespace std;
#define siz(x) (int)(x).size()
 
void solve(){
	stack<int> limit, over;
	int n, speed = 0, ans = 0;
	cin >> n;
	int a, b;
	for(int i=0; i<n ;i++){
		cin >> a;
		if(a == 1){
			cin >> speed;
			while(siz(limit) && limit.top() < speed)
				ans++,limit.pop();
         	}
		if(a == 2)
			while(siz(over) && !over.top())
				ans++,over.pop();
		if(a == 3){
			limit.push({});
			cin >> limit.top();
			if(limit.top() < speed)
				ans++,limit.pop();
		}
		if(a == 4)
			over.push(1);
		if(a == 5)
			limit.push(INT_MAX);
		if(a == 6)
			over.push(0);
	}
	cout << ans << "\n";
}
 
int main(){
   solve();
   return 0;
}
```


---

