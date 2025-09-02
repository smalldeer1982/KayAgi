# [ARC140B] Shorten ARC

## 题目描述

---

给出一个仅由 $A,R,C$ 组成的长度为 $n$ $(1\le n\le 2\times 10^5)$ 的字符串 $S$，您可以进行操作：

- 如果进行第奇数次操作，您需要用 $R$ 替换一次 $S$ 中的任意一个子串 $ARC$

- 如果进行第偶数次操作，您需要用 $AC$ 替换一次 $S$ 中的任意一个子串 $ARC$

最多能进行多少次操作？

翻译 by wukaichen888

## 样例 #1

### 输入

```
6
AARCCC```

### 输出

```
2```

## 样例 #2

### 输入

```
5
AAAAA```

### 输出

```
0```

## 样例 #3

### 输入

```
9
ARCARCARC```

### 输出

```
3```

# 题解

## 作者：Lucky_Cloud (赞：3)

## 分析
自然，我们可以想到利用贪心去解题。

我们可以证明，$\texttt{ARC}$ 左右两边 $\texttt{A}$ 和 $\texttt{C}$ 个数多的比少的变为 $\texttt{R}$ 贡献能更多，第奇数次操作比第偶数次能使操作次数更多。

于是，我们可以得出这样的一个算法：

1. 若为奇数次操作那我们将现有的 $\texttt{ARC}$ 中左右两边 $\texttt{A}$ 与 $\texttt{C}$ 最多的取出，将 $\texttt{AC}$ 的个数减一。
1. 若为偶数次操作那我们将现有的 $\texttt{ARC}$ 中左右两边 $\texttt{A}$ 与 $\texttt{C}$ 最少的取出，将其删除。

## Code

为了实现以上操作，我们采用 ```multiset``` 实现。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 100;
int n, x;
multiset<int> arc;
string s;

int main() {
	cin >> n;
	cin >> s;
	x = 2;
	for (int i = 1; i < s.size() - 1; i++) {//从一开始，避免数组越界
		if (s[i] == 'R') {//以 R 为中心，统计 A 与 C 的个数
			int k = 0, l = i - 1, r = i + 1;
			while (l >= 0 && r < s.size() && s[l] == 'A' && s[r] == 'C') {
				k++;
				l--, r++;//向两边扩展
			}
			if (k)//如果有 A 与 C
			arc.insert(k);
		}
	}
	int c = 0;
	while (arc.size()) {//只要不为空，那么我们还可以操作
		c++;
		if (c % x == 0) {
			arc.erase(arc.begin());//删除最小的，保个数多的，使答案最多
		}
		else {
			auto it = arc.end();
			it--;
			int y = *it;
			arc.erase(it);//取出最大的
			y--;
			if (y)  arc.insert(y);//若还能操作，就把他插回去
		}
	}
	cout << c << "\n";
	return 0;
}
```


---

## 作者：AirQwQ (赞：2)

## 前置知识

带删除的优先队列：



## 分析

注意到 $AARCC$ 这种字符串,在进行奇数操作后,还有可能继续被操作,但进行操作偶数后就不能再操作了。

所以我们可以知道如上所说类似 $AARCC$ 的子串越长，越应该用奇数次操作，反之用偶数次的操作。所以对所有子串按长度进行排序，支持动态排序的数据结构不难想到优先队列。

所以具体操作为：

1. 遍历整个字符串，找出所有满足 $A \dots ARC \dots C$ 的子串。

2. 构造两个可删除的优先队列，分别用大根堆，小根堆存储。

3. 按照题意模拟，取队首，去重，放回（[带删除优先队列](https://www.cnblogs.com/cnyali-Tea/p/10554660.html)基本操作）。



## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
string s;
priority_queue<int,vector<int>,less<int> >q1;
priority_queue<int,vector<int>,less<int> >q1a;
priority_queue<int,vector<int>,greater<int> >q2;
priority_queue<int,vector<int>,greater<int> >q2a;
int main(){
    cin>>n>>s;
    for(int i=1;i<n-1;i++){
        if(s[i-1]!='A'||s[i]!='R'||s[i+1]!='C')continue;
        int l=i-1,r=i+1;
        while(l&&s[l-1]=='A')
			l--;
        while(r<n-1&&s[r+1]=='C')
			r++;//易错点1：l，r其他写法忘-1，+1
        q1.push(min(i-l,r-i));
        q2.push(min(i-l,r-i));
    }
    while(1){
    	while(!q1.empty()&&!q1a.empty()&&q1.top()==q1a.top())
			q1.pop(),q1a.pop();
		while(!q2.empty()&&!q2a.empty()&&q2.top()==q2a.top())
			q2.pop(),q2a.pop();
		if(q1.empty()||q2.empty()) break;//判空
        if((ans+1)%2){//易错点4：ans初值为0，这里要+1
        	while(!q1.empty()&&!q1a.empty()&&q1.top()==q1a.top())
				q1.pop(),q1a.pop();
            int cnt=q1.top();
            q1a.push(cnt),q2a.push(cnt);
            if(cnt!=1)//易错点2：不减一或者不判0
            	q1.push(cnt-1),q2.push(cnt-1);
        }
		else{
            while(!q2.empty()&&!q2a.empty()&&q2.top()==q2a.top())
				q2.pop(),q2a.pop();
            int cnt=q2.top();//易错点3：下面多减一
            q1a.push(cnt),q2a.push(cnt);
            
        }
		ans++;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：RNTBW (赞：2)

### PART 0
众所周知，140 是一个奇妙的数字。

所以我有一个不用 ``set`` 的奇妙做法。

## PART 1
题意没什么好解释。

## PART 2
众所周知，形如 ``AAARCCC`` 这样的字符串是可以被循环利用多次的。

众所周知，如果我们对上述字符串执行操作 1，那么它会变为 ``AARCC``，可以继续利用。

但是如果对它执行了操作 2，那么它会变为 ``AAACCC``，无法继续利用。

所以众所周知，我们可以把每个**单独的** ``R`` 拎出来（像 ``AARRCC`` 这种有多个 ``R`` 的不存在 ``ARC`` 子串），求一下左边的 ``A`` 数量与右边的 ``C`` 数量再求个最小值。

这样我们就得到了这个 ``R`` 的最大利用价值，可以将它放进一个数组 $r$ 中。

## PART 3

众所周知，如果我们放任这个 ``R``，让它“自生自灭”，那么它最多只能产生 2 点贡献。

但是如果我们在操作 1 之后，不对它本身进行操作 2，而是由其它的 ``R`` 来进行，那么它还可以“苟活”一段时间，但是代替它执行“死刑”的那个 ``R`` 就死绝了。

这个做法，我们称之为“挡箭”。

它看似是没有用处的，因为虽然你对当前这个 ``R`` 多进行了一次操作 1，但是你让另一个 ``R`` 少了一次操作 1。

但是！

如果在这个整体操作中，代替当前 ``R``（设为 $R_1$）执行死刑的 ``R``（设为 $R_2$），$R_2$ 本身的最大价值就是 1 呢？

那意味着如果我们放任 $R_2$，它只会产生 1 点贡献。

但是如果我们让它不那么平平无奇地死去，而是让它代替 $R_1$ 挡一次“死刑”，那么它也产生了 1 点贡献，但是这可以让 $R_1$ 多产生 1 点贡献。

所以，我们可以在所有的 ``R`` 中，筛选出最大价值为 1 的，让它们去为最大价值更多的 ``R`` 挡死。

但是对于一个最大贡献大于 1 的 ``R``，为了节约宝贵的挡死资源，它只能接受不大于最大贡献减 2 次挡死，剩下的那两次就让它自己死掉。

举个例子：

``AAARCCCARCARC``，第一次在最左边的最大价值为 3 的那个 ``R`` 上进行操作 1，变为 ``AARCCARCARC``。

第二次我们用一个最大价值为 1 的 ``R`` 来代替它挡死，变为 ``AARCCARC``。

第三，第四次为了节约剩下的那个 ``ARC``，我们让这个 ``AARCC`` 自生自灭：

``AARCC`` $\to$ ``ARC`` $\to$ ``AC``

这样剩下的一个 ``ARC`` 就可以去为其它 ``R`` 挡死了。

## PART 4

处理出每个 ``R`` 的最大价值以后排序一下，便成了一个模拟题了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int r[200001];
int n,m,i,j,k,s,ans,now;
char a[200001];
int main()
{
	scanf("%d",&n);
	scanf("%s",a);
	for(i=0;i<n;i++)
	{
		if(a[i]=='R'&&a[i-1]!='R'&&a[i+1]!='R')
		{
			k=s=0;
			j=i-1;
			while(a[j]=='A') k++,j--;
			j=i+1;
			while(a[j]=='C') s++,j++;
			r[++m]=min(k,s);//处理每个R的最大价值
		}
	}k=0;s=m;//这里我们贪心一下，默认挡箭牌优先为最大价值更多的R服务
	sort(r+1,r+m+1);
	for(i=1;i<=m;i++)
		if(r[i]==1) k++,ans++;//找出1，即“挡箭牌”的数量
    //挡箭牌挡箭时会进行一次操作2，把它产生的贡献加上
	while(r[s]>1)
	{
		now=min(r[s]-2,k);//将当前挡箭牌的数量与当前R可接受的挡箭牌数量求个min
		k-=now;s--;//指针下移，为下一个R服务
		ans+=now+2;//2是当前R最后的两次自生自灭的操作
        //每有一个挡箭牌，当前的R就可以多一次操作1
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：A_Step_Back (赞：1)

# 思路分析

分析一下可以发现奇数次操作时，若存在 `AAA...ARCCC...C` 时，即 $x$ 个 `A` 和 $x$ 个 `C` 夹着一个 `R` 时，就可以反复消除；但偶数次操作后，这个片段就没有贡献了。

所以我们可以统计每个片段的使用次数，然后排个序（尽量让使用次数较少的片段被偶数次操作浪费掉）。

接着就用两个指针标记奇数操作的位置，和偶数操作的位置。注意偶数操作从小到大（尽量不要浪费太多），奇数操作两个方向均可。

最后，记得把剩余的 `ARC` 进行操作。

# 双手奉上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans,n,cnt,f[70005];char c[200005];
int main(){
	scanf("%d",&n);cin>>c;
	for(int i=1;i<=n-2;i++){
		if(c[i]=='R'){
			int j=1;
			while(c[i-j]=='A'&&c[i+j]=='C')j++;
			if(j==1)continue;//干脆不构成“ARC”
			else f[++cnt]=j-2;//用while会多算
		}
	}
	sort(f+1,f+cnt+1);
	int s=0,c=0;
	while(!f[s]&&s<=cnt+10)s++;
    
   	//s是奇数操作的指针，c是偶数s，可以从第一个大于0的值开始。
   	//若不存在这样的值，s应比cnt大（大多少本蒟蒻也想不清楚）
    
	while(s<=cnt){
		s=max(s,c+1);
		if(s>cnt)break;
		f[s]--;if(!f[s])s++;
		c++;
		ans+=2; 
	}
	ans+=cnt-c;//处理剩下的“ARC”
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：chenyyy (赞：0)

一看到题目就想到了贪心好吧，用 ``multiset`` 记录每个 ``R`` 旁边有多少个 ``A`` 和 ``C`` ，如果是奇数次操作，就选取最大的进行操作，反之选取最小的。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
multiset<int> s;//set会去重，不能用
int n;
string ss;
int main(){
    cin >> n >> ss;
    for(int i = 1;i < ss.size() - 1;i++){
        if(ss[i] == 'R'){
            int res = 0,j = i - 1,k = i + 1;
            while(j >= 0 && k < ss.size() && ss[j] == 'A' && ss[k] == 'C'){
                res++;//记录次数
                j--,k++;//向左右扫描
            }
            if(res){
            	s.insert(res);
			}
        }
    }
    int i = 1,ans = 0;//最开始是第一次操作，所以i=1
    while(s.size()){
    	if(i & 1){
    		auto i = s.end();
    		i--;//因为end()返回的是最后地址的下一个，所以要减一，最开始没写RE
    		if(*i != 1){
    			s.insert(*i - 1);
			}
			s.erase(i);
		}
		else s.erase(s.begin());
		ans++;
		i++;
	}
	cout << ans;
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/204807779)

---

## 作者：smartdevil (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc140_b)

## 题意：

题目说的挺像人话，没啥了。

## 思路：

不难发现奇数次操作，把 `ARC` 消除为 `R`，存在 `AAA....ARCC....CCC` 时可以疯狂刷贡献，但偶数此操作后就没贡献了。

统计每个片段的使用次数，然后排序。

然后用两个指针标记奇数次和偶数次操作的位置。偶数操作从小到大（减少浪费），奇数两个方向都行。

最后操作剩余的 `ARC` 就行了。

---

## 作者：XYQ_102 (赞：0)

## 题意
给定只含 `A`、`R`、`C` 的 $N$长度字符串，

在奇数次操作时可以将 `ARC` $\to$ `R`，

在偶数次操作时可以将 `ARC` $\to$ `AC`，

求可以操作的最大次数。
## 思路
在找到对应 `ARC` 后向左右扩展，然后判断可以得到奇数次扩展个数，不难观察到，偶数次不可能得到 `ARC`，并且会破坏现有的可供扩展的结构，所以这道题是双指针 $+$ 简单思维。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	string s;
	cin>>s;
	int ans=0,odd=0;
	for(int i=0;i<n-2;i++)
		if(s.substr(i,3)=="ARC") 
		{
			ans++;
			int l=i,r=i+2;
			while(l>0 && r<n && s[l-1]=='A' && s[r+1]=='C') 
			{
				l--;
				r++;
			}
			odd+=(i-l);
		}
	for(int i=0;i<ans;i++)
		if(i%2==0 && odd>0)
			odd--,ans++;
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：YBaggio (赞：0)

题面翻译里已经很明白了，不多加赘述。
## 思路
我们设奇数次操作为操作1，偶数次操作为操作2，形如 AAAAAAAA...ARCCCCCCC...C 的部分为块（ARC也是块）。

很明显，任何两个块都无法融合（因为一个块中，A不能出现在右边，C不能出现在左边）。

容易发现对于一个块，操作1做完之后，如果左边有A，右边有C则可以继续操作，而操作2操作完之后不能再进行操作，相当于废掉了这个块。

由于每次操作2都会废掉一个块，我们需要考虑废掉那个块。很明显，废掉 **“潜力”** 最小的块是最优的，同样，操作1操作“潜力”最大的方块是最优的。何为“潜力”，“潜力”就是该块所能进行操作的最多次数（操作1的最多次数），也就是一直对一个块做操作1，能做多少次操作。由于每次操作1都会消耗一个块里的一个A和一个C所以一个块最多能做 $ \min \{$ 块中A的数量 $,$ 块中C的数量 $\}$ 次操作，我们设第 $i$ 个块最多能做 $x_i$ 次操作，那么我们对于每次操作的最优方案为:
+ 操作1操作 $\max_{i=1}^{n}{x_i}$
+ 操作2操作 $\min_{i=1}^{n}{x_i}$

## 最后附上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
string s;
struct Heap{//找x[i]的最大最小值用堆来实现
    priority_queue<int>q;
    priority_queue<int>d;
    void push(int x){q.push(x);}
    void del(int x){d.push(x);}
    bool empty(){
        while(!d.empty()&&!q.empty()&&q.top()==d.top())q.pop(),d.pop();
        return q.empty();
    }
    int top(){
        while(!d.empty()&&!q.empty()&&q.top()==d.top())q.pop(),d.pop();
        return q.top();
    }
}a,b;
int main(){
    ios::sync_with_stdio(false);
    std::cin.tie(0);std::cout.tie(0);
    cin>>n>>s;
    for(int i=1;i<n-1;i++){
        if(s[i]!='R'||s[i-1]!='A'||s[i+1]!='C')continue;
        int l=i-1,r=i+1;
        while(l>0&&s[l-1]=='A')l--;
        while(r<n-1&&s[r+1]=='C')r++;
        a.push(min(i-l,r-i));//i-l为块中A的个数，r-i为块中C的个数
        b.push(-min(i-l,r-i));
    }//寻找块
    while(!a.empty()&&!b.empty()){
        if((ans+1)%2){//操作1操作潜力最大的
            int tmp=a.top();
            a.del(tmp);
            b.del(-tmp);
            tmp--;
            if(tmp)a.push(tmp),b.push(-tmp);
        }else{//操作2操作潜力最小的
            int tmp=-b.top();
            a.del(tmp);
            b.del(-tmp);
        }ans++;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

