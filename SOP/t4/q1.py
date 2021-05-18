def dist(a, b):
    return abs(a - b)


def find_min(diff):
    index = -1
    mini = float("inf")

    for i in range(len(diff)):
        if not diff[i][1] and mini > diff[i][0]:
            mini = diff[i][0]
            index = i
    return index


def ssf_sorting(requests):
    head = requests[0]
    l = len(requests)
    diff = [[0, 0] for _ in range(l)]
    seek_sequence = [0] * (l + 1)

    for i in range(l):
        seek_sequence[i] = head
        for i in range(len(diff)):
            diff[i][0] = abs(requests[i] - head)
        index = find_min(diff)
        diff[index][1] = True
        head = requests[index]
    seek_sequence[len(seek_sequence) - 1] = head
    return seek_sequence[1:]


def elevator_sorting(values, direction):
    # True if going ascending otherwise False
    actual = 0
    original_head, actual_head = values[0], values[0]
    left, right = [], []
    seek_sequence = []

    for i in range(len(values)):
        if values[i] < actual_head:
            left.append(values[i])
        if values[i] > actual_head:
            right.append(values[i])

    left.sort()
    right.sort()

    for _ in range(2):
        if direction:
            for i in range(len(right)):
                actual = right[i]
                seek_sequence.append(actual)
                actual_head = actual

            direction = not direction
        else:
            for i in range(len(left) - 1, -1, -1):
                actual = left[i]
                seek_sequence.append(actual)
                actual_head = actual

            direction = not direction
    seek_sequence = [original_head] + seek_sequence
    return seek_sequence


def fcfs(requests, deslocation_time, access_time):
    print("Sequencia de execução")
    print(*requests)

    print("Tempos parciais")
    total_time = 0
    for i in range(len(requests) - 1):
        actual, next = requests[i : i + 2]
        request_dist = dist(actual, next)
        request_time = request_dist * deslocation_time + access_time
        print(
            f"{actual} -> {next}: {request_dist * deslocation_time} + {access_time} = {round(request_time,2)} ms"
        )
        total_time += request_time
    print(f"Tempo total: {total_time} ms")


def ssf(requests, deslocation_time, access_time):
    requests = ssf_sorting(requests)
    fcfs(requests, deslocation_time, access_time)


def elevator(requests, deslocation_time, access_time, previous_direction):
    requests = elevator_sorting(requests, previous_direction == "right")
    fcfs(requests, deslocation_time, access_time)


requests = [100, 131, 174, 196, 110, 142, 149, 1, 172, 82, 18]

print("--== FCFS ==--")
fcfs(requests, 0.8, 6.25)

print("\n--== SSF ==--")
ssf(requests, 0.8, 6.25)

print("\n--= Elevator ==--")
elevator(requests, 0.8, 6.25, "right")
