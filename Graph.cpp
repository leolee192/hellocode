
/** 双向BFS 模板题 Leetcode 127 */

// q1、q2 为两个方向的队列
// m1、m2 为两个方向的哈希表，记录每个节点距离起点的

// 只有两个队列都不空，才有必要继续往下搜索
// 如果其中一个队列空了，说明从某个方向搜到底都搜不到该方向的目标节点
while(!q1.empty() && !q2.empty()) {
    if (q1.size() < q2.size()) {
        y = update(q1, m1, m2);
    } else {
        y = update(q2, m2, m1);
    }
    /** 通过update的返回值判断是否已找到答案 */
}

// update 为将当前队列 q 中包含的元素取出，进行「一次完整扩展」的逻辑（按层拓展）
void update(deque &q, map &cur, map &other) {
    int n = q.size();
    for (int i=0; i<n; ++i) {
        string node = q.front(); q.pop_front();

        for (adj: node.adjList) {
            /** 再次确定adj是否在可行集合里 */

            if (cur.find(adj) == cur.end()) {
                /** 更新cur */

                if (other.find(adj) != other.end()) {
                    /** 找到结果 */
                }

                q.push_back(adj);
            }
        }
    }
}

