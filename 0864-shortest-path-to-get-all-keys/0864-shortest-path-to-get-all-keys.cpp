class Solution {
    struct State {
    int row;
    int col;
    int keys;
    int distance;

    State(int r, int c, int k, int d) : row(r), col(c), keys(k), distance(d) {}
};
public:
    int shortestPathAllKeys(vector<string>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();

        int totalKeys = 0;
        int startRow = -1, startCol = -1;

        // Find the starting position and count the number of keys
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '@') {
                    startRow = i;
                    startCol = j;
                } else if (islower(grid[i][j])) {
                    totalKeys++;
                }
            }
        }

        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        vector<vector<vector<int>>> visited(m, vector<vector<int>>(n, vector<int>(64, 0)));
        // visited[i][j][k] stores the minimum distance to reach position (i, j) with keys bitmask k

        queue<State> q;
        q.emplace(startRow, startCol, 0, 0);
        visited[startRow][startCol][0] = 1;

        while (!q.empty()) {
            State curr = q.front();
            q.pop();

            int row = curr.row;
            int col = curr.col;
            int keys = curr.keys;
            int distance = curr.distance;

            if (keys == (1 << totalKeys) - 1) {
                return distance;  // All keys collected
            }

            for (const auto& dir : directions) {
                int newRow = row + dir[0];
                int newCol = col + dir[1];

                if (newRow < 0 || newRow >= m || newCol < 0 || newCol >= n ||
                    grid[newRow][newCol] == '#') {
                    continue;  // Out of grid or wall
                }

                char cell = grid[newRow][newCol];

                if (isupper(cell) && !(keys & (1 << (cell - 'A')))) {
                    continue;  // Lock encountered without key
                }

                int newKeys = keys;
                if (islower(cell)) {
                    newKeys |= 1 << (cell - 'a');  // Collect key
                }

                if (!visited[newRow][newCol][newKeys]) {
                    visited[newRow][newCol][newKeys] = 1;
                    q.emplace(newRow, newCol, newKeys, distance + 1);
                }
            }
        }

        return -1;  // No path to collect all keys
    }
};
