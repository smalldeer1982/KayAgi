# 题目信息

# Ordering Pizza

## 题目描述

It's another Start\[c\]up finals, and that means there is pizza to order for the onsite contestants. There are only 2 types of pizza (obviously not, but let's just pretend for the sake of the problem), and all pizzas contain exactly $ S $ slices.

It is known that the $ i $ -th contestant will eat $ s_{i} $ slices of pizza, and gain $ a_{i} $ happiness for each slice of type 1 pizza they eat, and $ b_{i} $ happiness for each slice of type 2 pizza they eat. We can order any number of type 1 and type 2 pizzas, but we want to buy the minimum possible number of pizzas for all of the contestants to be able to eat their required number of slices. Given that restriction, what is the maximum possible total happiness that can be achieved?

## 说明/提示

In the first example, you only need to buy one pizza. If you buy a type 1 pizza, the total happiness will be $ 3·5+4·6+5·9=84 $ , and if you buy a type 2 pizza, the total happiness will be $ 3·7+4·7+5·5=74 $ .

## 样例 #1

### 输入

```
3 12
3 5 7
4 6 7
5 9 5
```

### 输出

```
84
```

## 样例 #2

### 输入

```
6 10
7 4 7
5 8 8
12 5 8
6 11 6
3 3 7
5 9 6
```

### 输出

```
314
```

# AI分析结果

### 题目内容
# 订购披萨

## 题目描述
又到了创业公司决赛，这意味着要为现场参赛者订购披萨。披萨只有两种类型（显然不是，但为了题目我们就这么假设），并且每个披萨都恰好有 $S$ 片。

已知第 $i$ 个参赛者会吃 $s_{i}$ 片披萨，并且他们每吃一片第一种类型的披萨会获得 $a_{i}$ 的快乐值，每吃一片第二种类型的披萨会获得 $b_{i}$ 的快乐值。我们可以订购任意数量的第一种和第二种披萨，但我们希望购买尽可能少的披萨，以使所有参赛者都能吃到他们所需的片数。在这个限制条件下，能达到的最大总快乐值是多少？

## 说明/提示
在第一个示例中，你只需要买一个披萨。如果你买一个第一种类型的披萨，总快乐值将是 $3·5 + 4·6 + 5·9 = 84$，如果你买一个第二种类型的披萨，总快乐值将是 $3·7 + 4·7 + 5·5 = 74$。

## 样例 #1
### 输入
```
3 12
3 5 7
4 6 7
5 9 5
```
### 输出
```
84
```

## 样例 #2
### 输入
```
6 10
7 4 7
5 8 8
12 5 8
6 11 6
3 3 7
5 9 6
```
### 输出
```
314
```

### 算法分类
贪心

### 题解综合分析与结论
这两道题解均采用贪心策略解决问题。
 - **蒟酱题解**：先按吃哪种披萨快乐值更高进行分配，统计多出来的披萨片数。若多出来的片数之和大于一个披萨的片数，就保持当前分配；否则按吃两种披萨快乐值之差排序，调整人员的披萨类型以减少披萨购买数量，同时保证快乐值损失最小。
 - **LJ07题解**：先让所有人买第一种披萨，再按 $b_i - a_i$ 从大到小排序，每 $S$ 片披萨一组判断是否将部分人换成第二种披萨，通过增加一个“凑数”的人使总片数是 $S$ 的倍数来保证购买最少份数的披萨。

蒟酱题解思路和代码实现相对更清晰，LJ07题解引入“凑数”人思路较难理解且代码可读性稍差。

### 所选的题解
 - **蒟酱题解**：
   - **星级**：4星
   - **关键亮点**：思路清晰，先贪心分配再调整，通过计算多余披萨片数和按快乐值之差排序来优化披萨购买数量和总快乐值。
   - **重点代码核心思想**：先遍历输入数据，按吃哪种披萨快乐值高进行分配并统计多余片数，再对快乐值之差进行排序，逐步调整人员的披萨类型以优化结果。
   - **核心代码片段**：
```cpp
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);cin.tie(nullptr);
	cin>>n>>m;
	for(int c,a,b;n--;)if(cin>>c>>a>>b,a>b){
		ans+=a*c;
		b1.emplace_back(a-b,c);
		s1+=c;
	}else{
		ans+=b*c;
		b2.emplace_back(b-a,c);
		s2+=c;
	}
	s1%=m;s2%=m;
	if(s1+s2>m)return cout<<ans,0;
	sort(all(b1));
	sort(all(b2));
	for(auto[k1,k2]:b1){
		c1+=min(k2,s1)*k1;
		s1-=min(k2,s1);
		if(s1<=0)break;
	}
	for(auto[k1,k2]:b2){
		c2+=min(k2,s2)*k1;
		s2-=min(k2,s2);
		if(s2<=0)break;
	}
	cout<<ans-min(c1,c2);
	return 0;
}
```

### 最优关键思路或技巧
1. **贪心策略**：先按快乐值高低初步分配披萨，再根据多余披萨片数和快乐值之差调整，以达到购买最少披萨且总快乐值最大。
2. **排序优化**：通过对快乐值之差排序，保证调整过程中快乐值损失最小。

### 可拓展之处
此类题目属于贪心策略在资源分配场景的应用，类似套路可应用于其他资源分配且需优化某一指标的题目，例如不同物品有不同价值和重量，在背包容量限制下求最大价值等。

### 洛谷相似题目推荐
1. **P1094 [NOIP2007 普及组] 纪念品分组**：通过贪心策略对物品进行分组，在一定限制条件下求最少分组数。
2. **P1223 排队接水**：按照接水时间从小到大排序，贪心选择接水顺序，使总等待时间最短。
3. **P1993 小K的农场**：结合贪心思想和差分约束系统解决问题，与本题同样涉及到对条件的分析和优化求解。 

---
处理用时：39.34秒