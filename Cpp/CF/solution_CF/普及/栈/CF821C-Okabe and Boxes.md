# Okabe and Boxes

## 题目描述

Okabe and Super Hacker Daru are stacking and removing boxes. There are $ n $ boxes numbered from $ 1 $ to $ n $ . Initially there are no boxes on the stack.

Okabe, being a control freak, gives Daru $ 2n $ commands: $ n $ of which are to add a box to the top of the stack, and $ n $ of which are to remove a box from the top of the stack and throw it in the trash. Okabe wants Daru to throw away the boxes in the order from $ 1 $ to $ n $ . Of course, this means that it might be impossible for Daru to perform some of Okabe's remove commands, because the required box is not on the top of the stack.

That's why Daru can decide to wait until Okabe looks away and then reorder the boxes in the stack in any way he wants. He can do it at any point of time between Okabe's commands, but he can't add or remove boxes while he does it.

Tell Daru the minimum number of times he needs to reorder the boxes so that he can successfully complete all of Okabe's commands. It is guaranteed that every box is added before it is required to be removed.

## 说明/提示

In the first sample, Daru should reorder the boxes after adding box $ 3 $ to the stack.

In the second sample, Daru should reorder the boxes after adding box $ 4 $ and box $ 7 $ to the stack.

## 样例 #1

### 输入

```
3
add 1
remove
add 2
add 3
remove
remove
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7
add 3
add 2
add 1
remove
add 4
remove
remove
remove
add 6
add 7
add 5
remove
remove
remove
```

### 输出

```
2
```

# 题解

## 作者：李至擎 (赞：4)

[点我看题](https://www.luogu.com.cn/problem/CF821C)

题目大意：
```
开始时，小明有1到n总共n个数。现在，他要执行n次将数字入栈和n次将数字出栈的操作。出栈时，他希望按照1、2、3、...n的顺序出栈。所以，在遇到无法完成时，他就会先用魔法把目前栈里所有的数按上小下大的顺序排列，然后再执行操作。问小明在过程中最少执行几次魔法。

操作分为两种，每次的格式如下：

add x：将x这个数入栈；

remove：将栈顶数字出栈。
```

思路一：~~暴力~~根据题意进行模拟：

结果：在第⑨个点[TLE](https://www.luogu.com.cn/record/44496251)了（也许有dalao能优化一些，但是应该是过不去的）。

是啊，每次在出栈操作时如果都进行一次排序操作的话，时间复杂度将难以想象。那么，我们还有更好的方法吗？答案是肯定的。

思路二：既然第二种操作时的排序操作是主要耗时，那么，我们不妨来对它进行优化。

优化方法：每次遇到第二种操作时直接清空栈里的所有元素，不用进行排序。

为什么我们可以进行这样的优化呢？因为，每次进行排序时，由于出栈顺序固定，所以接下来的所有元素在此次排完序后以后出栈时的顺序也是如此，即我们不需要再进行思考，直接无视即可。

可能有些难以理解。那么，我们用一组样例来解释一下——假设操作为：

```
add 1
add 4
add 3
remove
add 2
remove
remove
remove
```

显然答案是 $1$ ，即第一次出栈操作的唯一一次。

那么，如果按照第二种方法，答案又是多少呢？——还是 $1$ 。不信，自己去试试。也可以试试再举几组数据，当然，你会惊奇的发现它们的答案都是对的。这时，再结合我上面的解释，相信你会有更深刻的理解。

方法就不讲啦，自认为上面已经讲得够清楚了。如果还有不懂的地方，请结合代码和注释食用。

代码：

```cpp
#include<bits/stdc++.h>
#define LL long long//个人习惯 
using namespace std;
int a[300005];//a数组是模拟的栈（因为真正的栈清空不太方便）
int n,x,l,num=1,ans;//n和x如题意，l是栈的长度，num是当前要去除的数，ans是使用魔法的次数 
char opt[15];//opt是输入的工具字符串 
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++)//一共2*n个操作 
	{
		scanf("%s",opt);
		if(opt[0]=='a')//如果它是入栈操作 
		{
			scanf("%d",&x);//输入要入栈的数 
			a[++l]=x;//压进栈 
		}
		else
		{
			if(a[l]!=0)//如果栈里还有数 
			{
				if(num!=a[l])//如果栈顶与当前需求不同 
				{
					l=0;//清空栈 
					ans++;//使用一次魔法 
				}
				else l--;//去掉了一个数，长度-1					
			}
			num++;//变成下一个要去除的数 
		}
	}
	printf("%d",ans);//输出结果 
	return 0;//结束程序 
}
```

---

## 作者：A_zjzj (赞：3)

### 一道模拟题

每一次 add 的时候，就不用管直接扔进栈里面，因为你在这个时候排个序不如之后 remove 的时候排序。

然后每一次 remove 的时候。

如果栈顶是当前要出栈的数，那么直接让他出去。

否则，就需要排一次序，把答案加一。

因为这样已经拍过序了，所以之后的已经不用排了，那么就直接把这些数全部出栈，后面如果要出栈时，栈为空，那么这个要出栈的书一定是在之前就出去了。

```cpp
#include<cstdio>
using namespace std;
int n,x,s[300001],top,ans;
char c[10];
int main(){
	scanf("%d",&n);
	for(int i=1,k=0;i<=(n<<1);i++){
		scanf("%s",c+1);
		if(c[1]=='a'){
			scanf("%d",&x);
			s[++top]=x;
		}
		else{
			k++;
			if(!top)continue;
			if(s[top]!=k){
				top=0;
				ans++;
			}
			else top--;
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：kuaiCreator (赞：2)

# CF821C Okabe and Boxes 题解  
## 题目大意 
有任意入栈或出栈操作各 $n$ 次 $n\le3×10^5$。每次入栈会将 $1-n$ 中的任意一个入栈。并且**保证一个数在需要被弹出之前一定被加入过**。要求出栈顺序为 $1-n$。问最少需要调整多少次。 
## 题目思路
编写代码之前先分析时间、空间复杂度和数据范围。 $n$ 的数据范围为 $n≤3×10^5$ 需要时间复杂度为 $O(n\log{n})$ 或效率更高的方法，需要一个栈空间复杂度为 $O(n)$，数据范围在 int 范围内。  

### 部分分思路： 直接模拟
  
若是 remove 操作，因为可能存在多次 remove 操作故可以记录一下 remove 操作的次数，等到下一次 add 操作或最后再统一出栈并判断。

若是 add 操作则先处理之前的若干次 remove 操作，对于每次 remove 操作。  
1. 若当前应出栈元素与栈顶元素相同则首先应出栈元素编号加一，然后元素出栈，最后 remove 操作减少一次。
2. 若当前应出栈元素与栈顶元素不相同，则考虑可以把栈从栈底到栈顶从小到大排序，并全部处理完。

显然数据最后都是 remove 操作，故在 $n\times 2$ 次操作后，再将未处理的 remove 操作单独处理，处理方式与之前类似。

直接模拟的部分分代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int q, x, now = 1, stack[300005], top, cnt;
	int ans = 0;
	string s;
	cin >> q;
	q *= 2;
	while (q--) {
		cin >> s;
		if (s == "add") {
			while (cnt) {
				if (now == stack[top]) {
					top--;
					now++;
					cnt--;
				} else {
					sort(stack + 1, stack + 1 + top);
					ans++;
					top -= cnt;
					now += cnt;
					cnt = 0;
				}
			}
			cin >> x;
			stack[++top] = x;
		} else if (s == "remove") {
			cnt++;
		}
	}
	while (cnt) {
		if (now == stack[top]) {
			top--;
			now++;
			cnt--;
		} else {
			sort(stack + 1, stack + 1 + top);
			ans++;
			top -= cnt;
			now += cnt;
			cnt = 0;
		}
	}
	cout << ans;
	return 0;
}
```
### 100分思路： 模拟+优化

根据数据范围，显然方法一会超时，考虑优化算法。

在处理 remove 操作时，选择了将栈排序，这是导致超时的原因。考虑到当前操作为 remove 时，如果栈顶元素与应出栈元素不同，我们如果调整肯定会将栈中的所有元素调整为我们期望的出栈顺序，因此后面如果再有没有遇到 add 操作时，**所有的当前栈内元素个数次的** remove 操作都是不需要调整的。即使遇到新的 add 操作，该操作所对应的 remove 操作也必须合法时才可以不调整。

得到以上结论，我们可以选择在 remove 操作且当栈顶元素与应出栈元素不同时，直接将栈清空。如果后续遇到remove 操作时，栈为空则说明该出栈操作的数是已经被调整过的合法出栈数。

满分代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	int q, x, num = 1, st[300005], top = 0;
	int ans = 0;
	string s;
	cin >> q;
	q *= 2;
	while (q--) {
		cin >> s;
		if (s == "add") {
			cin >> x;
			st[++top] = x;
		} else if (s == "remove") {
			if (top != 0) { //若栈空标书操作已被调整为合法顺序，不为空则判断是否要调整。          
				if (st[top] == num) //如果新入栈的元素等于num说明不用调整
					top--;
				else {
					top = 0;
					ans++;
				}
			}
			num++;
		}
	}
	cout << ans;
	return 0;
}
```

---

