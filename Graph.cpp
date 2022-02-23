
/** ˫��BFS ģ���� Leetcode 127 */

// q1��q2 Ϊ��������Ķ���
// m1��m2 Ϊ��������Ĺ�ϣ����¼ÿ���ڵ��������

// ֻ���������ж����գ����б�Ҫ������������
// �������һ�����п��ˣ�˵����ĳ�������ѵ��׶��Ѳ����÷����Ŀ��ڵ�
while(!q1.empty() && !q2.empty()) {
    if (q1.size() < q2.size()) {
        y = update(q1, m1, m2);
    } else {
        y = update(q2, m2, m1);
    }
    /** ͨ��update�ķ���ֵ�ж��Ƿ����ҵ��� */
}

// update Ϊ����ǰ���� q �а�����Ԫ��ȡ�������С�һ��������չ�����߼���������չ��
void update(deque &q, map &cur, map &other) {
    int n = q.size();
    for (int i=0; i<n; ++i) {
        string node = q.front(); q.pop_front();

        for (adj: node.adjList) {
            /** �ٴ�ȷ��adj�Ƿ��ڿ��м����� */

            if (cur.find(adj) == cur.end()) {
                /** ����cur */

                if (other.find(adj) != other.end()) {
                    /** �ҵ���� */
                }

                q.push_back(adj);
            }
        }
    }
}

