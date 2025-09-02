# Long Jumps

## 题目描述

Valery 是 Berland 学校的一名体育老师。学生们将参加跳远测试，但 Valery 丢失了他最喜欢的尺子！不过，Valery 没有失落，因为他找到了另一把尺子，它的长度为 $l$ 厘米。这个尺子上已经有 $n$ 个刻度，可以用来进行测量。

我们假设这些刻度是按照从尺子起始到结束的顺序编号的。第一个刻度与尺子的起点重合，表示原点。最后一个刻度与尺子的末尾重合，距离原点为 $l$。这把尺子可以表示为一个递增的数列 $a_1, a_2, ..., a_n$，其中 $a_i$ 表示第 $i$ 个刻度离原点的距离 ($a_1=0, a_n=l$)。

Valery 认为，如果存在一对整数 $i$ 和 $j$ ($1 \leq i \leq j \leq n$)，使得第 $i$ 个刻度和第 $j$ 个刻度之间的距离恰好等于 $d$，即 $a_j - a_i = d$，那么就可以用尺子测量 $d$ 厘米的距离。

根据规定，女生应该至少能够跳 $x$ 厘米，男生应该至少能够跳 $y$ 厘米 ($x < y$)。为了测试学生的能力，Valery 需要尺子能够测量出这两个距离 $x$ 和 $y$。

你的任务是确定最少需要增加多少个刻度，使得尺子能够测量这两个距离 $x$ 和 $y$。你可以在尺子上添加任何整数非负距离，且不超过尺子长度 $l$。

## 说明/提示

在第一个示例中，初始尺子无法测量 $230$ 厘米的距离。只需增加 $230$ 厘米的刻度，或者 $20$ 厘米的刻度就可以了。

在第二个示例中，尺子已经能够测量 $185$ 厘米和 $230$ 厘米的距离，因此无需增加新的刻度。

在第三个示例中，尺子只有初始和末尾两个刻度。为了能够测试学生的能力，我们需要增加 $185$ 和 $230$ 厘米的刻度。

## 样例 #1

### 输入

```
3 250 185 230
0 185 250
```

### 输出

```
1
230
```

## 样例 #2

### 输入

```
4 250 185 230
0 20 185 250
```

### 输出

```
0
```

## 样例 #3

### 输入

```
2 300 185 230
0 300
```

### 输出

```
2
185 230
```

# 题解

## 作者：DennyQi (赞：0)

先考虑能不能从原序列中找出差值为$x$与$y$的数对。由于序列具有单调性，我们枚举终点二分起点，这样就可以$O(n \log n)$判断了。（也可以用队列来维护，这样是$O(n)$）

接下来考虑如果找不到怎么办。如果能够找到$x$或$y$的其中一个，既然无论如何都得加一个，不如加在缺失的那个位置。如果没有$x$那就加$y$，如果没有$y$那就加$x$。

考虑两个都没有。那么我们可以一个长度为$(x+y)$的数对中间插一个，或者在一段长度为$(y-x)$的两端插一个。我们二分检查$(x+y)$与$(y-x)$是否存在即可。

对于剩余的情况，那只能加两个了，那就加$x$和$y$好了。

在判断$y-x$的地方需要注意，可能有多个$(y-x)$满足条件，但有的可能插入位置为越界。我们要找能满足条件的$(y-x)$
```cpp
/*DennyQi 2019*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 100010;
inline int read(){
    int x(0),w(1); char c = getchar();
    while(c^'-' && (c<'0' || c>'9')) c = getchar();
    if(c=='-') w = -1, c = getchar();
    while(c>='0' && c<='9') x = (x<<3)+(x<<1)+c-'0', c = getchar(); 
    return x*w;
}
int n,l,r,mid,x,y,a[N],ans[5];
inline int check(int len){
	int l,r,mid;
	for(int i = 2; i <= n; ++i){
		l = 1, r = i-1;
		while(l <= r){
			mid = (l+r) >> 1;
			if(a[i]-a[mid] > len){
				l = mid + 1;
			}
			else if(a[i]-a[mid] < len){
				r = mid - 1;
			}
			else if(a[i]-a[mid] == len){
				return a[mid];
			}
		}
	}
	return -1;
}
int main(){
	// freopen("file.in","r",stdin);
	n = read(), l = read(), x = read(), y = read();
	for(int i = 1; i <= n; ++i){
		a[i] = read();
	}
	ans[0] = check(x);
	ans[1] = check(y);
	ans[2] = check(x+y);
	ans[3] = check(y-x);
	// printf(">>>>> ANS: %d %d %d %d\n",ans[0],ans[1],ans[2],ans[3]);
	if(ans[0]!=-1 && ans[1]!=-1){
		printf("0\n");
		return 0;
	}
	if(ans[0]!=-1 && ans[1]==-1){
		printf("1\n%d\n",y);
		return 0;
	}
	if(ans[0]==-1 && ans[1]!=-1){
		printf("1\n%d\n",x);
		return 0;
	}
	if(ans[2]!=-1){
		printf("1\n%d\n",ans[2]+x);
		return 0;
	}
	for(int i = 2; i <= n; ++i){
		l = 1, r = i-1;
		while(l <= r){
			mid = (l+r) >> 1;
			if(a[i]-a[mid] > y-x){
				l = mid + 1;
			}
			else if(a[i]-a[mid] < y-x){
				r = mid - 1;
			}
			else if(a[i]-a[mid] == y-x){
				if(a[mid]-x > 0){
					printf("1\n%d\n",a[mid]-x);
					return 0;
				}
				if(a[mid]+y < a[n]){
					printf("1\n%d\n",a[mid]+y);
					return 0;
				}
				break;
			}
		}
	}
	printf("2\n%d %d\n",x,y);
	return 0;
}
```

---

