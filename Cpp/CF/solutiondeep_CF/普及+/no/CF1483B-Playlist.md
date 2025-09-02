# 题目信息

# Playlist

## 题目描述

Arkady has a playlist that initially consists of $ n $ songs, numerated from $ 1 $ to $ n $ in the order they appear in the playlist. Arkady starts listening to the songs in the playlist one by one, starting from song $ 1 $ . The playlist is cycled, i. e. after listening to the last song, Arkady will continue listening from the beginning.

Each song has a genre $ a_i $ , which is a positive integer. Let Arkady finish listening to a song with genre $ y $ , and the genre of the next-to-last listened song be $ x $ . If $ \operatorname{gcd}(x, y) = 1 $ , he deletes the last listened song (with genre $ y $ ) from the playlist. After that he continues listening normally, skipping the deleted songs, and forgetting about songs he listened to before. In other words, after he deletes a song, he can't delete the next song immediately.

Here $ \operatorname{gcd}(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

For example, if the initial songs' genres were $ [5, 9, 2, 10, 15] $ , then the playlist is converted as follows: \[5, 9, 2, 10, 15\] $ \to $ \[5, 9, 2, 10, 15\] $ \to $ \[5, 2, 10, 15\] (because $ \operatorname{gcd}(5, 9) = 1 $ ) $ \to $ \[5, 2, 10, 15\] $ \to $ \[5, 2, 10, 15\] $ \to $ \[5, 2, 10, 15\] $ \to $ \[5, 2, 10, 15\] $ \to $ \[5, 2, 10, 15\] $ \to $ \[5, 10, 15\] (because $ \operatorname{gcd}(5, 2) = 1 $ ) $ \to $ \[5, 10, 15\] $ \to $ \[5, 10, 15\] $ \to $ ... The bold numbers represent the two last played songs. Note that after a song is deleted, Arkady forgets that he listened to that and the previous songs.

Given the initial playlist, please determine which songs are eventually deleted and the order these songs are deleted.

## 说明/提示

Explanation of the first test case is given in the statement.

In the second test case, the playlist is converted as follows: \[1, 2, 4, 2, 4, 2\] $ \to $ \[1, 2, 4, 2, 4, 2\] $ \to $ \[1, 4, 2, 4, 2\] (because $ \operatorname{gcd}(1, 2) = 1 $ ) $ \to $ \[1, 4, 2, 4, 2\] $ \to $ \[1, 4, 2, 4, 2\] $ \to $ \[1, 4, 2, 4, 2\] $ \to $ \[1, 4, 2, 4, 2\] $ \to $ \[1, 4, 2, 4, 2\] $ \to $ \[4, 2, 4, 2\] (because $ \operatorname{gcd}(2, 1) = 1 $ ) $ \to $ \[4, 2, 4, 2\] $ \to $ ...

In the third test case, the playlist is converted as follows: \[1, 2\] $ \to $ \[1, 2\] $ \to $ \[1\] (because $ \operatorname{gcd}(1, 2) = 1 $ ) $ \to $ \[1\] $ \to $ \[1\] (Arkady listened to the same song twice in a row) $ \to $ \[\] (because $ \operatorname{gcd}(1, 1) = 1 $ ).

The fourth test case is same as the third after deletion of the second song.

In the fifth test case, the same song is listened to over and over again, but since $ \operatorname{gcd}(2, 2) \ne 1 $ , it is not deleted.

## 样例 #1

### 输入

```
5
5
5 9 2 10 15
6
1 2 4 2 4 2
2
1 2
1
1
1
2```

### 输出

```
2 2 3 
2 2 1 
2 2 1 
1 1 
0```

# AI分析结果

### 题目翻译
Arkady 有一个播放列表，最初包含 $n$ 首歌曲，按它们在播放列表中出现的顺序从 $1$ 到 $n$ 编号。Arkady 开始逐个收听播放列表中的歌曲，从歌曲 $1$ 开始。播放列表是循环的，即听完最后一首歌后，Arkady 将继续从开头收听。

每首歌曲都有一个流派 $a_i$，这是一个正整数。假设 Arkady 听完了一首流派为 $y$ 的歌曲，且倒数第二首收听歌曲的流派为 $x$。如果 $\gcd(x, y) = 1$，他就会从播放列表中删除最后收听的歌曲（流派为 $y$）。之后他会继续正常收听，跳过已删除的歌曲，并忘记之前收听的歌曲。换句话说，删除一首歌曲后，他不能立即删除下一首歌曲。

这里 $\gcd(x, y)$ 表示整数 $x$ 和 $y$ 的[最大公约数 (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor)。

例如，如果初始歌曲的流派为 $[5, 9, 2, 10, 15]$，那么播放列表的转换过程如下：$[5, 9, 2, 10, 15] \to [5, 9, 2, 10, 15] \to [5, 2, 10, 15]$（因为 $\gcd(5, 9) = 1$）$\to [5, 2, 10, 15] \to [5, 2, 10, 15] \to [5, 2, 10, 15] \to [5, 2, 10, 15] \to [5, 10, 15]$（因为 $\gcd(5, 2) = 1$）$\to [5, 10, 15] \to [5, 10, 15] \to \cdots$ 粗体数字表示最后播放的两首歌曲。请注意，删除一首歌曲后，Arkady 会忘记他收听的那首歌和之前的歌曲。

给定初始播放列表，请确定最终会删除哪些歌曲以及这些歌曲被删除的顺序。

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟歌曲删除的过程，通过不同的数据结构和方法来优化暴力模拟的时间复杂度。主要的优化点在于避免重复计算相邻歌曲对的 $\gcd$。

- **思路对比**：大部分题解都采用了链表来维护歌曲的顺序和删除操作，同时使用队列来存储需要判断的相邻歌曲对，避免重复计算。也有部分题解使用集合（set）来维护关键元素或剩余的歌曲。
- **算法要点**：
    - 链表：用于高效地删除歌曲和查找相邻歌曲。
    - 队列：存储需要判断的相邻歌曲对，按顺序处理。
    - 集合：维护关键元素或剩余的歌曲，方便查找和删除。
- **解决难点**：
    - 避免重复计算：通过队列或集合来记录需要判断的歌曲对，避免重复判断已经处理过的对。
    - 循环处理：处理播放列表的循环特性，确保所有歌曲都能被处理。
    - 删除操作：在删除歌曲后，需要更新链表或集合的状态，确保后续操作的正确性。

### 高星题解
- **vectorwyx（4星）**
    - **关键亮点**：思路清晰，代码简洁，详细解释了暴力解法和优化思路，使用队列和链表的组合优化了时间复杂度。
    - **核心代码**：
```cpp
void del(int x){
    R[L[x]]=R[x];
    L[R[x]]=L[x];
}

void work(){
    int n=read();
    top=w=0;
    fo(i,1,n) a[i]=read(),L[i]=i-1,R[i]=i+1,d[i]=0;
    L[1]=n,R[n]=1;
    fo(i,1,n-1) s1[++top]=i,s2[top]=i+1;
    s1[++top]=n,s2[top]=1;
    fo(i,1,top){
        if(w==n) break;
        if(d[s1[i]]||d[s2[i]]) continue;
        int g=__gcd(a[s1[i]],a[s2[i]]);
        if(g==1){
            ans[++w]=s2[i];
            d[s2[i]]=1;
            s1[++top]=s1[i];
            s2[top]=R[s2[i]];
            del(s2[i]);
        } 
    }
    printf("%d ",w);fo(i,1,w) printf("%d ",ans[i]);puts("");
}
```
核心实现思想：首先读取输入，初始化链表和队列，然后不断从队列中取出相邻歌曲对，判断它们的 $\gcd$ 是否为 $1$，如果是则删除后一首歌曲，并更新链表和队列。

- **__galaxy_1202__（4星）**
    - **关键亮点**：详细解释了优化思路，代码结构清晰，使用队列和链表实现了模拟过程。
    - **核心代码**：
```cpp
while (!(Q.empty()))
{
    int ai = Q.front().first, bi = Q.front().second;
    Q.pop();
    if (vis[ai]) continue;
    if (__gcd(val[ai], val[bi]) == 1)
    {
        vis[bi] = 1;
        r[ai] = r[bi];
        Q.push({ai, r[ai]});
        x.push_back(bi);
    }
}
```
核心实现思想：从队列中取出相邻歌曲对，判断 $\gcd$ 是否为 $1$，如果是则删除后一首歌曲，更新链表和队列，并记录删除的歌曲。

### 最优关键思路或技巧
- 使用链表来维护歌曲的顺序和删除操作，能够高效地进行删除和查找相邻元素。
- 使用队列来存储需要判断的相邻歌曲对，避免重复计算，将时间复杂度从 $O(n^2k)$ 优化到 $O(nk)$。

### 可拓展之处
同类型题可能涉及其他规则的模拟，例如不同的删除条件或播放规则。类似的算法套路包括使用链表和队列来优化模拟过程，避免重复计算。

### 推荐洛谷题目
- P1047 [NOIP2005 普及组] 校门外的树
- P1098 [NOIP2007 提高组] 字符串的展开
- P1160 队列安排

### 个人心得摘录与总结
- **Cry_For_theMoon**：ARC 掉分后脑子抽，2C 卡了 1h，最后 2：05 的时候 pp 了这个题最后成功上分。样例 RE 一个，加个特判后最后一遍 pp 就 A 了。总结：做题时可能会遇到思路卡顿和样例错误的情况，及时调整和添加特判可能会解决问题。

---
处理用时：50.82秒