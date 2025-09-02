# Second price auction

## 题目描述

Nowadays, most of the internet advertisements are not statically linked to a web page. Instead, what will be shown to the person opening a web page is determined within 100 milliseconds after the web page is opened. Usually, multiple companies compete for each ad slot on the web page in an auction. Each of them receives a request with details about the user, web page and ad slot and they have to respond within those 100 milliseconds with a bid they would pay for putting an advertisement on that ad slot. The company that suggests the highest bid wins the auction and gets to place its advertisement. If there are several companies tied for the highest bid, the winner gets picked at random.

However, the company that won the auction does not have to pay the exact amount of its bid. In most of the cases, a second-price auction is used. This means that the amount paid by the company is equal to the maximum of all the other bids placed for this ad slot.

Let's consider one such bidding. There are $ n $ companies competing for placing an ad. The $ i $ -th of these companies will bid an integer number of microdollars equiprobably randomly chosen from the range between $ L_{i} $ and $ R_{i} $ , inclusive. In the other words, the value of the $ i $ -th company bid can be any integer from the range $ [L_{i},R_{i}] $ with the same probability.

Determine the expected value that the winner will have to pay in a second-price auction.

## 说明/提示

Consider the first example. The first company bids a random integer number of microdollars in range $ [4,7] $ ; the second company bids between $ 8 $ and $ 10 $ , and the third company bids $ 5 $ microdollars. The second company will win regardless of the exact value it bids, however the price it will pay depends on the value of first company's bid. With probability $ 0.5 $ the first company will bid at most $ 5 $ microdollars, and the second-highest price of the whole auction will be $ 5 $ . With probability $ 0.25 $ it will bid $ 6 $ microdollars, and with probability $ 0.25 $ it will bid $ 7 $ microdollars. Thus, the expected value the second company will have to pay is $ 0.5·5+0.25·6+0.25·7=5.75 $ .

## 样例 #1

### 输入

```
3
4 7
8 10
5 5
```

### 输出

```
5.7500000000
```

## 样例 #2

### 输入

```
3
2 5
3 4
1 6
```

### 输出

```
3.5000000000
```

# 题解

## 作者：TTpandaS (赞：0)

答案为 

$$ \sum_{i=1}^{\max_{j=1}^{n} r_j} i \cdot p_i $$

直接求 $i$ 作为次大的概率 $p_i$ 是不方便的，所以将答案转换为求次大不低于 $i$ 的概率 $f_i$，所以:

$$ p_i=f_i-f_{i+1} $$

枚举次大值 $k$，最后要求的肯定是前 $n$ 个人中有 $j$ 个人出价不低于 $k$ 的概率，所以 $dp_{i,j}$ 状态定义为前 $i$ 个人中有 $j$ 个人出价不低于 $k$ 的概率，所以：

$$ f_k= \sum_{j=1}^{n}dp_{n,j} $$

第 $i$ 个人出价不低于 $k$ 的概率为：

$$ \dfrac{r_i-\max(l_i,k)+1}{r_i-l_i+1} $$

令 

$$ P=\dfrac{r_i-\max(l_i,k)+1}{r_i-l_i+1}  $$

所以有 $P$ 的概率多一人出价不低于 $k$，有 $1-P$ 的概率出价不低于 $k$ 的人数不变，所以内层枚举出价不低于 $k$ 的人数，转移为：

$$ dp_{i,j}= dp_{i-1,j-1} \cdot P +dp_{i-1,j} \cdot (1-P)$$

---

