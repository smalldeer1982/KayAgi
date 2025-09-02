# After Training

## 题目描述

After a team finished their training session on Euro football championship, Valeric was commissioned to gather the balls and sort them into baskets. Overall the stadium has $ n $ balls and $ m $ baskets. The baskets are positioned in a row from left to right and they are numbered with numbers from $ 1 $ to $ m $ , correspondingly. The balls are numbered with numbers from $ 1 $ to $ n $ .

Valeric decided to sort the balls in the order of increasing of their numbers by the following scheme. He will put each new ball in the basket with the least number of balls. And if he's got several variants, he chooses the basket which stands closer to the middle. That means that he chooses the basket for which ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF195B/a806f5bf21bc9e79268695bcfcf77ba78839a96f.png) is minimum, where $ i $ is the number of the basket. If in this case Valeric still has multiple variants, he chooses the basket with the minimum number.

For every ball print the number of the basket where it will go according to Valeric's scheme.

Note that the balls are sorted into baskets in the order of increasing numbers, that is, the first ball goes first, then goes the second ball and so on.

## 样例 #1

### 输入

```
4 3
```

### 输出

```
2
1
3
2
```

## 样例 #2

### 输入

```
3 1
```

### 输出

```
1
1
1
```

# 题解

## 作者：letianJOE (赞：2)

# 题目大意

$n$ 个球，$m$ 个框，每次把球放在现有球最少的地方，如有多个，选最靠近中间的框，还有多个，就选最左边的。初始每个框没有球，输出每个球应该放在哪个框。

---

# 思路

## 想法

需要运用贪心以及一点点分类讨论。

首先，$n$ 和 $m$ 的数据范围都到了 $10^5$，那么正常的模拟肯定过不了，我们尝试使用线性算法。

然而，尝试了 dp，硬是 d 不出来。然后就想用贪心试一下，发现可以。

我们发现每一次放的篮框总是呈对称的，也就是类似中左右左右左右中的顺序，所以就可以用贪心了。

---

什么意思呢？我们来看下面这组样例。

$n$ 为 $9$，$m$ 为 $5$，

那么我们要先选中间的 $3$，然后选左，也就是 $2$，然后再选右，也就是 $4$，然后第四第五选 $1$ 和 $5$。再回到中间，继续执行上面的操作，知道篮球用完。

---

先分两类讨论，$m$ 是奇数还是偶数。

### 奇数

如果是奇数，那么会有一个框在中间，那么我们先选中间那个框，然后左右左右选即可。

### 偶数

如果是偶数，就是先选 $m \div 2$ 的框，然后选它的右边，然后就又是左右左右左右选。

---

但是实际写的时候细节会比较多。

## 具体做法

首先，我们定义两个变量，$now$ 和 $f$。

$now$ 用来存放现在遍历的位置

$f$ 用来状态，也就是在中间、左边还是右边，便于 $now$ 的变化。

这两个数只需要按照想法变化即可。

那么，我们还需要判断是否越界，也就是投到小于 1 或者大于 $m$ 的框，那么就要变成 $1$ 或 $m$。

顺带提一嘴，这题的代码好像厌氧。

---

# CODE

`Talk is cheap.Show me the code. —— Aprendiz`

细节在代码中有体现。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,now,f;
signed main()
{
	cin>>n>>m;
	if(m%2==1)
	{
		now=m/2+1,f=3;
		for(int i=1;i<=n;i++)
		{
			cout<<now<<"\n";
			if(f==3)
				now--,f=1;
			else if(f==1)
				f=2,now=m-now+1;
			else
			{
				if(now==m)
					now=m/2+1,f=3;
				else
					f=1,now=m-now;
			}
		if(now<1)
			now=1;
		if(now>m)
			now=m;
		}
	}
	else
	{
		now=m/2,f=1;
		for(int i=1;i<=n;i++)
		{
			cout<<now<<"\n";
			if(f==1)
				now=m-now+1,f=2;
			else
			{
				if(now==m)
					now=m/2;
				else
					now=m-now;
				f=1;
			}
		}
	}
	return 0;
}
```


---

## 作者：sxq9 (赞：2)

## 思路
按照规则，我们会发现其实放的方法就是：中间，左边，右边，因为每次找中间的，然后拿一个之后就不能拿了，接着找左边最靠近的，再找右边的，拿完之后再重新拿中间，以此类推。

左边到右边就是 $m-pos+1$，右边到左边是 $m-pos$。
## AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	double mid=(m+1)*1.0/2;
	int pos=mid;
	if(m==1)pos=1;
	for(int i=1;i<=n;i++){
		cout<<pos<<endl;
		if(pos==m)pos=mid;
		else pos=m-pos+(int)(pos<mid);//左边就是加一，右边不加
	}
	return 0;
}
```

---

## 作者：XXh0919 (赞：1)

通过读题我们可以发现：其实放球的顺序就是中间，左边，右边，一直循环往复，即：先把球放进中间的筐里，然后找左边离中间筐最近的筐，放进去，接着找右边的，然后新一轮再放中间，以此类推。

最后我们可以发现：放在中间是 $(m+1)\div2$ 处的筐，从右边移到左边是 $m-p$ 处的筐，从左边移到右边的是 $m-p+1$ 处的筐。

还有一个的特判，就是当 $p=m$ 时（即所有筐都放了一遍），就需要将 $(m+1)\div2$ 赋值给 $p$，即开启新的一轮放置。

**AC Code：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
int p;
signed main(){
  scanf("%lld %lld",&n,&m);
  double mid=(m+1)*1.0/2;
  p=mid;//以下用 mid 代替 (m+1)/2
  if(m==1)p=1;
  for(int i=1;i<=n;i++){
    printf("%lld\n",p);
    if(p==m)p=mid;//特判
    else if(p<mid)p=m-p+1;//从左到右
    else p=m-p;//从右到左
  }
  return 0;
}
```

---

## 作者：foryou_ (赞：1)

结论题。

首先第一次放置一定处于中间，即 $pos = \lfloor \dfrac{m+1}{2} \rfloor$ 处，其中 $pos$ 为当前放置的位置。

接下来要放置的位置可能在现在位置的左边或右边。

我们可以猜测到最终的放置方式应当为先左后右，以此类推。

进一步的：

- 若 $pos$ 左边对称的篮筐没有被放置（判断 $pos$ 是否 $<mid$，是则被放置了。$mid$ 为正中间的位置），则根据题目给出的优先级，接下来一定放置在其对称的左边篮筐，即 $m-pos$ 处；

- 否则放在它右边对称的的篮框中，即 $m-pos+1$ 处。

上面的结论建议自行画图理解。

同时，还有一个特判，就是当 $pos=m$ 时（说明所有篮筐都放了一遍），则需要令 $pos=mid$（即重新开始放一轮）。

有了上面的结论，代码就很好写了。时间复杂度 $O(n)$。

---

## 作者：_int123_ (赞：0)

题目：

## After Training

### 题意

有 $n$ 个球，要放入 $m$ 个篮筐中。对于每次的投放：

1. 放入已有球数最小的框中。

2. 如有多种情况，选择最靠近中间的。

3. 在同样靠近中间的球中，选择最靠左的。

问每个球应放入第几个框中。

### 思路：

我们可以分奇偶讨论。

#### 1. $m$ 为奇数

我们首先选最中间的那一个，即第 $ \left( m+1 \right) \div 2$ 个，然后再贴着已选过的左右左右去选，直到都放过一次以后再从中间开始放。

#### 2. $m$ 为偶数

我们首先选最中间靠左的那一个，即第 $m \div 2$ 个，然后选它右边的那一个，再贴着已选过的左右左右去选，直到都放过一次以后再从中间靠左的开始放。

### AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件 
#define int long long//保险起见，开了 long long 
using namespace std;
int n,m;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加速 
	cin>>n>>m;//输入 
	double mid=(m+1)*1.0/2;//取最中间的位置（可以不是球） 
	int q=mid;
	for(int i=1;i<=n;i++)
	{
		cout<<q<<'\n';//输出 
		if(q==m) q=mid;//选完了再从中间选 
		else if(q<mid) q=m-q+1;//左->右 
		else q=m-q;//右->左
	}
	return 0;
}
```

完结撒花！！！

---

## 作者：zfw100 (赞：0)

# CF195B After Training 题解

## 题目分析

贪心加上分类讨论。

找规律，我们可以发现：由于一开始所有篮筐皆为空，所以第一个一定是放在中间的，而若篮筐有偶数个，则无中间，所以按照题意应该放在编号为 $m\div2$ 的筐里。所以要分奇偶进行讨论。

 - 奇数 
 
 那么第一个应该放在编号为 $(m+1)\div2$ 的筐里，之后按照左右左右的方式放，若放完了则反复。
 
 - 偶数
 
 直接左右左右放即可，第一个应该放在编号为 $m\div2$ 的筐里。
 
 又由于 C++ 语言自动向下取整，所以直接使用 `now=(m+1)/2` 即可。
 
 代码不放了。

---

## 作者：ImNot6Dora (赞：0)

根据第三条，容易发现篮筐数量为偶数和奇数的两种情况分别对应两种摆放顺序。

如果篮筐数量为奇数，则第一次放在中间，第二次左，第三次右，以此类推，直到全部摆放上一个小球后，继续再从中间开始，如下图：

![奇数](https://cdn.luogu.com.cn/upload/image_hosting/y7ugytc6.png?x-oss-process=image/resize,m_lfit,h_6500,w_6500)

如果为偶数，那么其中间就是两个篮筐了，此时，我们先选左侧的，再选右侧的，随后左右左右，以此类推，知道全部摆放一个小球后，再继续从中间开始。如下图：

![偶数](https://cdn.luogu.com.cn/upload/image_hosting/l56t065c.png?x-oss-process=image/resize,m_lfit,h_6500,w_6500)

那么搞懂思路后，代码就非常简单了。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	int k=m%2?m/2+1:m/2,p=1;
	bool f=1;
	for(int i=1;i<=n;i++){
		cout<<k<<endl;
		if(k==m){
			k=m%2?m/2+1:m/2;
			p=1;
			f=1;	
		}else{
			if(f)m%2?k-=p:k+=p;
			else m%2?k+=p:k-=p;
			p++;
			f=!f;
		}
	}
	return 0;
}
 
```


---

## 作者：qiuqiuqzm (赞：0)

# After Training 题解
[题目传送门](https://www.luogu.com.cn/problem/CF195B)

## 题目大意
给定 $n$ 个球和 $m$ 个框，让你依次把这些球按照规则投入进框中。规则如下：

$1$.放入已有球数最小的框中。

$2$.如有多种情况，选择最靠近中间的。

$3$.在同样靠近中间的球中，选择最靠左的。

问每个球应放入第几个框中。

## 分析
我们看到这道题，很容易就可以发现规律。那就是先中间，再左，再右重复。然后如果所有框都投了一遍，就重新从中间开始。

但是如果是偶数的话，没有最中间的数字，所以要从靠左的开始，可以把一开始的桶从 $m/2$ 号，改成 $(m+1)/2$ 号。而开始后，本来是要先往左的，但是已经从靠左的开始了，所以要改成先往右。

## Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,now,to=-1;
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	now=(m+1)/2; //这样写奇偶都不会影响
	for(int i=1;i<=n;i++)
	{
		cout<<now<<endl;
		if(m%2==0 && now==(m+1)/2) //如果是偶数，一开始先向右
			to=1;
		now+=to;
		to*=-1;
		if(to<0)
			to--;
		else
			to++;
		if(now<1 || now>m) //全部投了一遍
			now=(m+1)/2,to=-1;
	}
	return 0;
}
```

---

## 作者：__1d0h8dp__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF195B)

## 思路

本题很水……

根据题意，我们可以看出输出顺序是：从中间开始，先输出左边，再输出右边。

我们可以模拟第一个样例：

我们先找出中间的桶，也就是第二个桶。

对于第二个球，我们要找往左边的一个桶，也就是第一个桶。我们之所以要找这个桶，是因为题目说了，对于距离中间一样的桶，要找最靠左边的一个桶。

对于第三个球，我们要找第三个桶。

对于第四个球，我们要再装到第二个桶里，因为三个桶装的球数量一样。

**但是，偶数是另一个情况：**

我们找到中间后，要先从右边开始，因为有两个桶离中间的距离一样。当有四个桶时，我们的输出便变成了：
```
2
3
1
4
```
为什么是这样呢？因为共有 $4$ 个桶，一半是 $2.5$，依题意，中间的桶（即编号距离 $2.5$ 桶最近的桶）分别为二号和三号桶。二号桶要排在三号桶之前，三号要在一号之前，而四号要在最后，因此，顺序才会是这样的。

## 实现方法

我们要分两类讨论，即当 $m$ 是奇数的时候和当 $m$ 是偶数的时候。

实现方法其实不难，两种的实现方法基本上一样。可以定义一个 $now$ 变量，表示这一次选择的桶与上一次选择的桶的差距。

当 $m$ 是奇数时，如果 $now$ 是奇数，那这一次选择的桶的编号会比上一次选择的大，否则，如果 $now$ 是偶数，则是变小。

当 $m$ 是偶数时，与奇数相反。

为什么呢？

前面讲过，当 $m$ 为偶数时，第一次选择的时候回有两个桶距离中间的距离会是一样的，所以第一次要加，而不是减。

当现在要选择的桶编号小于 $0$ 或者大于 $m$ 的时候，便重新开始，从中间开始往外遍历。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	int curr=m/2; //从中间开始
	if(m%2) curr+=1;
	int now=0;
	for(int i=1;i<=n;i++){
		now++;
		printf("%d\n",curr); 
		if(m%2==1) { //分两类讨论
			if(now%2==0) curr+=now;
			else curr-=now;
 		}
		else {
			if(now%2==0) curr-=now;
			else curr+=now;
		}
		if(curr<1||curr>m){ //重新开始
			curr=m/2;
			if(m%2) curr+=1;
			now=0;
		}
	}
	cout<<endl;
	return 0;
}
```

**请勿抄题解！**

---

