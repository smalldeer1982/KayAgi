# [CERC2016] 关键的膝盖 Key Knocking

## 题目描述

Goran正在从他的膝盖手术中恢复，并正在试验用于存储的智能卡加密密钥。在这个问题中，一个密钥是指一个长度为3n的二进制序列，其中n是正整数。序列的每一位从左往右依次被编号为1到3n。一个密钥的权值是指相邻位不同的位置个数再加上1。比如：“000”的权值是1，“011010100”的权值是7。


他发现他可以发送小型脉冲电流来修改智能卡的电路，从而修改密钥。确切地说，他可以不断进行下面的操作：选择任意两个相邻的位，然后同时取反它们。比如他可以通过一次操作把“000”修改为“110”。


给定一个长度为3n的密钥，请操作不超过n次，将其修改为一个权值不少于2n的密钥。你可以认为合法解必然存在。


## 样例 #1

### 输入

```
111001000111
```

### 输出

```
2
3 9
```

# 题解

## 作者：342zhuyongqi (赞：3)

利用构造法贪心求解。

因为可以操作n次，一共3n个，所以可以把每3个分成一组

一共有8种可能

000

111 

011

100

110

001

010

101

对于010 101不用改变

对于011 100换前2个

对于110 001换后2个

对于111 000看前面就行了

```cpp
#include<stdio.h>
#include<string.h>
int n;
char a[300010];
int ans[100010],ans2;
int idx,sum,t;
#define a1 (i-1)*3+1
#define a2 (i-1)*3+2
#define a3 (i-1)*3+3
int main()
{
	scanf("%s",a+1);
	int l=strlen(a+1);
	for(int i=1;i<=l;i++)
		a[i]=a[i]-'0';
	for(int i=1;i<=l;i++)
		if(a[i]!=a[i+1])
			ans2++;
	if(ans2>=l/3*2+1)
	{
		printf("0");
		return 0;
	}
	for(int i=1;i<=l/3;i++)
	{
		if((a[a1]==a[a2])&&(a[a2]!=a[a3]))
		{
			sum++;
			if(a[a2]==1)
				a[a2]=0;
			else
				a[a2]=1;
			if(a[a3]==1)
				a[a3]=0;
			else
				a[a3]=1;			
			ans[++idx]=a2;
		}
		else if((a[a1]!=a[a2])&&(a[a2]!=a[a3]))
			continue;
		else if((a[a1]!=a[a2])&&(a[a2]==a[a3]))
		{
			sum++;
			if(a[a2]==1)
				a[a2]=0;
			else
				a[a2]=1;
			if(a[a1]==1)
				a[a1]=0;
			else
				a[a1]=1;			
			ans[++idx]=a1;			
		}
		else
		{
			if(a[a1]==a[(i-1)*3])
			{
				sum++;
				if(a[a1]==1)
					a[a1]=0;
				else
					a[a1]=1;
				if(a[a2]==1)
					a[a2]=0;
				else
					a[a2]=1;			
				ans[++idx]=a1;				
			}
			else
			{
				sum++;
				if(a[a3]==1)
					a[a3]=0;
				else
					a[a3]=1;
				if(a[a2]==1)
					a[a2]=0;
				else
					a[a2]=1;			
				ans[++idx]=a2;				
			}
		}
	}
	printf("%d\n",sum);
	for(int i=1;i<=sum;i++)
	{
		if(i!=sum)
			printf("%d ",ans[i]);
		else 
			printf("%d",ans[i]);		
	}
}
```

---

## 作者：Link_Cut_Y (赞：1)

神秘构造。

考虑怎么样才能使 $01$ 对个数增加。

首先发现修改一个对，会影响四个位置的 $01$ 对个数。也即修改 $i, i + 1$ 两个位置，那么 $i - 1, i + 2$ 两个位置的 $01$ 对也会收到影响。

因此考虑每个以 $i$ 为开头的长度为 $4$ 的段。贪心地考虑，如果是形如 $0110$ 或者 $1001$ 的形式，那么修改 $i, i + 1$ 两个位置（即中间两个位置）可以增加一对。

如果形如 $0000$ 或者 $1111$，那么修改 $i + 1, i + 2$ 可以增加两对。

如果形如 $0011$ 或者 $1100$，修改 $i + 1, i + 2$ 可以增加两对。

剩下的情况（$0101, 1010, 0010, 1101, 1110, 0001$ 等）可以按照上述思路处理。

于是随便写个代码就可以得到六十五分的高分。

```cpp
vector<int> vec;
char s[N]; int a[N], n;
int main() {
	scanf("%s", s + 1); n = strlen(s + 1);
	rep(i, 1, n) a[i] = s[i] ^ 48; 
	int cnt = 0;
	for (int i = 1; i + 3 <= n; i ++ ) {
		int &_0 = a[i], &_1 = a[i + 1], &_2 = a[i + 2], &_3 = a[i + 3];
		if (_0 and _1 and (!_2) and !(_3))
			_1 ^= 1, _2 ^= 1, cnt ++ , vec.push_back(i + 1);
		else if ((!_0) and (!_1) and _2 and _3 and cnt < n)
			_1 ^= 1, _2 ^= 1, cnt ++ , vec.push_back(i + 1);
		else if ((!_0) and (!_1) and (!_2) and (!_3))
			_1 ^= 1, _2 ^= 1, cnt ++ , vec.push_back(i + 1);
		else if (_0 and _1 and _2 and _3)
			_1 ^= 1, _2 ^= 1, cnt ++ , vec.push_back(i + 1);
		if (cnt == n / 3) break;
	}
	printf("%d\n", (int)vec.size());
	for (auto i : vec) printf("%d ", i); return 0;
}
```

继续考虑怎么优化这个贪心。发现不同策略的权值不同，这是不好处理的。要尽量将权值变得相同。

不难想到缩小讨论的区间长度。将每段区间长度从 $4$ 设置为 $3$。讨论个数缩小为 $8$ 个：

- $001$ 或 $110$：修改后两个点，增加一对。

- $100$ 或 $011$：修改前两个点，增加一对。

- $111$ 或 $000$：根据前面选择修改前面还是后面两个点，增加一对或两对。

- $101$ 或 $010$：无论怎么修改都不会增加。

```cpp
vector<int> vec;
char s[N]; int a[N], n, cnt;
int main() {
	scanf("%s", s + 1); n = strlen(s + 1);
	rep(i, 1, n) a[i] = s[i] ^ 48; 
	rep(i, 1, n / 3) {
		int &x = a[(i - 1) * 3 + 1], &y = a[(i - 1) * 3 + 2], &z = a[(i - 1) * 3 + 3];
		if (!x and !y and z) y ^= 1, z ^= 1, cnt ++ , vec.pb((i - 1) * 3 + 2);
		else if (x and y and !z) y ^= 1, z ^= 1, cnt ++ , vec.pb((i - 1) * 3 + 2); 
		else if (!x and y and z) x ^= 1, y ^= 1, cnt ++ , vec.pb((i - 1) * 3 + 1);
		else if (x and !y and !z) x ^= 1, y ^= 1, cnt ++ , vec.pb((i - 1) * 3 + 1);
		else if (x and y and z) {
			if (i != 1 and a[(i - 2) * 3 + 3])
				cnt ++ , vec.pb((i - 1) * 3 + 1);
			else y ^= 1, z ^= 1, cnt ++ , vec.pb((i - 1) * 3 + 2);
		} else if (!x and !y and !z) {
			if (i != 1 and !a[(i - 2) * 3 + 3])
				cnt ++ , vec.pb((i - 1) * 3 + 1);
			else y ^= 1, z ^= 1, cnt ++ , vec.pb((i - 1) * 3 + 2);
		}
		if (cnt == n / 3) break;
	}
	printf("%d\n", (int)vec.size());
	for (auto i : vec) printf("%d ", i); return 0;
}
```

---

