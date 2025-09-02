# 题目信息

# Vlad and a Pair of Numbers

## 题目描述

Vlad found two positive numbers $ a $ and $ b $ ( $ a,b>0 $ ). He discovered that $ a \oplus b = \frac{a + b}{2} $ , where $ \oplus $ means the [bitwise exclusive OR](http://tiny.cc/xor_wiki_eng) , and division is performed without rounding..

Since it is easier to remember one number than two, Vlad remembered only $ a\oplus b $ , let's denote this number as $ x $ . Help him find any suitable $ a $ and $ b $ or tell him that they do not exist.

## 样例 #1

### 输入

```
6
2
5
10
6
18
36```

### 输出

```
3 1
-1
13 7
-1
25 11
50 22```

# AI分析结果

### 题目内容重写
# Vlad 和一对数字

## 题目描述

Vlad 找到了两个正整数 $a$ 和 $b$（$a,b>0$）。他发现 $a \oplus b = \frac{a + b}{2}$，其中 $\oplus$ 表示[按位异或](http://tiny.cc/xor_wiki_eng)，且除法不进行四舍五入。

由于记住一个数字比记住两个数字更容易，Vlad 只记住了 $a\oplus b$，我们把这个数字记为 $x$。请你帮助他找到任何合适的 $a$ 和 $b$，或者告诉他这样的数字不存在。

## 样例 #1

### 输入

```
6
2
5
10
6
18
36
```

### 输出

```
3 1
-1
13 7
-1
25 11
50 22
```

---

### 题解综合分析

本题的核心在于通过给定的 $x$ 找到满足 $a \oplus b = \frac{a + b}{2} = x$ 的两个正整数 $a$ 和 $b$。多个题解通过不同的思路和技巧解决了这个问题，主要分为以下几类：

1. **数学推导**：通过异或和加法的性质，推导出 $a$ 和 $b$ 的表达式，并判断是否存在解。
2. **打表找规律**：通过打表观察规律，发现当 $x$ 为偶数且不包含连续两位为1时，存在解。
3. **二进制逐位处理**：通过逐位分析 $x$ 的二进制表示，构造出 $a$ 和 $b$。

### 精选题解

#### 题解1：灵茶山艾府 (★★★★★)
**关键亮点**：
- 通过数学推导，结合异或和加法的性质，得出了 $a$ 和 $b$ 的表达式。
- 代码简洁高效，时间复杂度为 $\mathcal{O}(1)$。
- 详细解释了无解的条件，逻辑清晰。

**核心代码**：
```go
func main() {
	in := bufio.NewReader(os.Stdin)
	var T, xor int
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &xor)
		and := xor >> 1
		if xor&1 > 0 || xor&and > 0 {
			Println(-1)
		} else {
			Println(xor|and, and)
		}
	}
}
```
**实现思想**：通过计算 $a \operatorname{and} b$ 和 $a \operatorname{xor} b$，判断是否存在解，并构造出 $a$ 和 $b$。

#### 题解2：幻想繁星 (★★★★☆)
**关键亮点**：
- 通过打表找规律，发现当 $x$ 有解时，$a$ 最小为 $\frac{x}{2}$，$b = \frac{3x}{2}$。
- 代码简洁，易于理解。

**核心代码**：
```cpp
int main() {
	int t=read();
	while(t--) {
		int x=read(),a=x/2,b=x*2-a;
		if((a^b)==x) cout<<a<<" "<<b<<"\n";
		else cout<<"-1\n";
	}
	return 0;
}
```
**实现思想**：通过构造 $a$ 和 $b$，判断是否满足条件。

#### 题解3：Night_sea_64 (★★★★☆)
**关键亮点**：
- 通过逐位分析 $x$ 的二进制表示，判断是否存在解。
- 详细解释了无解的条件，逻辑清晰。

**核心代码**：
```cpp
int main() {
	int t; cin>>t;
	while(t--) {
		int x; cin>>x;
		if(x%2) { cout<<-1<<endl; continue; }
		int y=2*x,cur=0,a=0,b=0;
		bool flag=1;
		while(y) {
			if(x%2==0) {
				if(x/2%2!=y/2%2) a=a+(1<<cur),b=b+(1<<cur);
			} else {
				if(y%2==0) {
					if(x/2%2==y/2%2) { flag=0; break; }
				} else if(x/2%2!=y/2%2) { flag=0; break; }
				a=a+(1<<cur);
			}
			x/=2,y/=2; cur++;
		}
		if(!flag) cout<<-1<<endl;
		else cout<<a<<" "<<b<<endl;
	}
	return 0;
}
```
**实现思想**：通过逐位分析 $x$ 的二进制表示，构造出 $a$ 和 $b$，并判断是否满足条件。

### 最优关键思路
1. **数学推导**：通过异或和加法的性质，推导出 $a$ 和 $b$ 的表达式，并判断是否存在解。
2. **打表找规律**：通过打表观察规律，发现当 $x$ 为偶数且不包含连续两位为1时，存在解。
3. **二进制逐位处理**：通过逐位分析 $x$ 的二进制表示，构造出 $a$ 和 $b$。

### 可拓展之处
- 类似的问题可以通过数学推导或打表找规律来解决。
- 二进制逐位处理的方法可以应用于其他涉及位运算的问题。

### 推荐题目
1. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)
2. [P1582 倒水](https://www.luogu.com.cn/problem/P1582)
3. [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)

### 个人心得
- **调试经历**：在逐位分析时，需要注意进位的情况，否则容易出错。
- **顿悟感想**：通过打表找规律，可以快速发现问题的本质，减少推导的时间。

---
处理用时：43.52秒