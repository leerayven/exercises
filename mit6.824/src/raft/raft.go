package raft

//
// this is an outline of the API that raft must expose to
// the service (or tester). see comments below for
// each of these functions for more details.
//
// rf = Make(...)
//   create a new Raft server.
// rf.Start(command interface{}) (index, term, isleader)
//   start agreement on a new log entry
// rf.GetState() (term, isLeader)
//   ask a Raft for its current term, and whether it thinks it is leader
// ApplyMsg
//   each time a new entry is committed to the log, each Raft peer
//   should send an ApplyMsg to the service (or tester)
//   in the same server.
//

import "sync"
import "labrpc"
import "meth/rand"

// import "bytes"
// import "encoding/gob"

//
// as each Raft peer becomes aware that successive log entries are
// committed, the peer should send an ApplyMsg to the service (or
// tester) on the same server, via the applyCh passed to Make().
//
type State int

const (
	Follower State = iota
	Candidate
	Leader
)

type ApplyMsg struct {
	Index       int
	Command     interface{}
	UseSnapshot bool   // ignore for lab2; only used in lab3
	Snapshot    []byte // ignore for lab2; only used in lab3
}

//
// A Go object implementing a single Raft peer.
//
type Entry struct {
	term    int
	command interface{}
}

type EventType int

const (
	evAppendEntry   EventType = iota
	evRequestVote
    evGetState
    evStartCommand
)

type reqEvent struct {
	evType      EventType
    args        interface{}
    replyCh     chan interface{}
}

type Raft struct {
	mu        sync.Mutex          // Lock to protect shared access to this peer's state
	peers     []*labrpc.ClientEnd // RPC end points of all peers
	persister *Persister          // Object to hold this peer's persisted state
	me        int                 // this peer's index into peers[]

	state State
	// Persistent state on all servers
	currentTerm int
	votedFor    int
	log         map[int]Entry

	//Volatile state on all servers
	commitIndex int
	lastApplied int

	// for leaders
	nextIndex  []int
	matchIndex []int
	// Your data here (2A, 2B, 2C).
	// Look at the paper's Figure 2 for a description of what
	// state a Raft server must maintain.
    eventCh     chan reqEvent
    lastLogTerm     int
    lastLogIndex    int
}

// return currentTerm and whether this server
// believes it is the leader.
type replyState struct {
    term        int
    isleader    bool
}
func (rf *Raft) GetState() (int, bool) {

	var term int
	var isleader bool
	// Your code here (2A).
    req := reqEvent{}
    req.evType = evGetState
    req.replyCh = make(chan interface{})
    rf.eventCh <- req
    reply := (<- req.replyCh).(replyState)
    term = reply.term
    isleader = reply.isleader
	return term, isleader
}

//
// save Raft's persistent state to stable storage,
// where it can later be retrieved after a crash and restart.
// see paper's Figure 2 for a description of what should be persistent.
//
func (rf *Raft) persist() {
	// Your code here (2C).
	// Example:
	// w := new(bytes.Buffer)
	// e := gob.NewEncoder(w)
	// e.Encode(rf.xxx)
	// e.Encode(rf.yyy)
	// data := w.Bytes()
	// rf.persister.SaveRaftState(data)
}

//
// restore previously persisted state.
//
func (rf *Raft) readPersist(data []byte) {
	// Your code here (2C).
	// Example:
	// r := bytes.NewBuffer(data)
	// d := gob.NewDecoder(r)
	// d.Decode(&rf.xxx)
	// d.Decode(&rf.yyy)
	if data == nil || len(data) < 1 { // bootstrap without any state?
		return
	}
}

//
// example RequestVote RPC arguments structure.
// field names must start with capital letters!
//
type RequestVoteArgs struct {
	// Your data here (2A, 2B).
    term            int
    candidateId     int
    lastLogIndex    int
    lastLogTerm     int
}

//
// example RequestVote RPC reply structure.
// field names must start with capital letters!
//
type RequestVoteReply struct {
	// Your data here (2A).
	term        int
    voteGranted bool
}

//
// example RequestVote RPC handler.
//
func (rf *Raft) RequestVote(args *RequestVoteArgs, reply *RequestVoteReply) {
	// Your code here (2A, 2B).
}

//
// example code to send a RequestVote RPC to a server.
// server is the index of the target server in rf.peers[].
// expects RPC arguments in args.
// fills in *reply with RPC reply, so caller should
// pass &reply.
// the types of the args and reply passed to Call() must be
// the same as the types of the arguments declared in the
// handler function (including whether they are pointers).
//
// The labrpc package simulates a lossy network, in which servers
// may be unreachable, and in which requests and replies may be lost.
// Call() sends a request and waits for a reply. If a reply arrives
// within a timeout interval, Call() returns true; otherwise
// Call() returns false. Thus Call() may not return for a while.
// A false return can be caused by a dead server, a live server that
// can't be reached, a lost request, or a lost reply.
//
// Call() is guaranteed to return (perhaps after a delay) *except* if the
// handler function on the server side does not return.  Thus there
// is no need to implement your own timeouts around Call().
//
// look at the comments in ../labrpc/labrpc.go for more details.
//
// if you're having trouble getting RPC to work, check that you've
// capitalized all field names in structs passed over RPC, and
// that the caller passes the address of the reply struct with &, not
// the struct itself.
//
func (rf *Raft) sendRequestVote(server int, args *RequestVoteArgs, reply *RequestVoteReply) bool {
	ok := rf.peers[server].Call("Raft.RequestVote", args, reply)
	return ok
}

type AppendEntryArgs struct {
	term         int
	leaderId     int
	prevLogIndex int
	prevLogTerm  int
	entries      map[int]Entry
	leaderCommit int
}

type AppendEntryReply struct {
    term        int
    success     bool
}

func (rf *Raft) AppendEntry(args *AppendEntryArgs, reply *AppendEntryReply) {

}

func (rf *Raft) sendAppendEntry(server int, args *AppendEntryArgs, reply *AppendEntryReply) bool {
    ok := rf.peers[server].Call("Raft.AppendEntry", args, reply)
    return ok
}
//
// the service using Raft (e.g. a k/v server) wants to start
// agreement on the next command to be appended to Raft's log. if this
// server isn't the leader, returns false. otherwise start the
// agreement and return immediately. there is no guarantee that this
// command will ever be committed to the Raft log, since the leader
// may fail or lose an election.
//
// the first return value is the index that the command will appear at
// if it's ever committed. the second return value is the current
// term. the third return value is true if this server believes it is
// the leader.
//
type replyStart struct {
    index       int
    term        int
    isLeader    int
}

func (rf *Raft) Start(command interface{}) (int, int, bool) {
	index := -1
	term := -1
	isLeader := true

	// Your code here (2B).
    req := reqEvent{}
    req.evType = evStartCommand
    req.args = command
    req.replyCh = make(chan replyStart)
    rf.eventCh <- req
    reply := (<- req.replyCh).(replyStart)
    index = reply.index
    term = reply.term
    isLeader = reply.isLeader

	return index, term, isLeader
}

//
// the tester calls Kill() when a Raft instance won't
// be needed again. you are not required to do anything
// in Kill(), but it might be convenient to (for example)
// turn off debug output from this instance.
//
func (rf *Raft) Kill() {
	// Your code here, if desired.
}

//
// the service or tester wants to create a Raft server. the ports
// of all the Raft servers (including this one) are in peers[]. this
// server's port is peers[me]. all the servers' peers[] arrays
// have the same order. persister is a place for this server to
// save its persistent state, and also initially holds the most
// recent saved state, if any. applyCh is a channel on which the
// tester or service expects Raft to send ApplyMsg messages.
// Make() must return quickly, so it should start goroutines
// for any long-running work.
//

func (rf *Raft)handle_evAppendEntry(req *reqEvent) bool {
    args := req.args.(AppendEntryArgs)
    reply := AppendEntryReply{}
    reEnter = false
    if args.term < rf.currentTerm {
        reply.term = rf.currentTerm
        reply.success = false
    } else {
        reEnter = true
        rf.state = Follower
        reply.term = args.term
        rf.term = args.term
        if rf.log[args.prevLogIndex] == args.prevLogTerm {
            reply.success = true
            conflict := false
            lastIndex := 0
            for i, e := range args.entries {
                if e1, ok := rf.log[i]; ok {
                    if rf.log[i].term != e.term {
                        conflict = true
                    }
                }
                lastIndex = i
                rf.log[i] = e
            }

            if args.leaderCommit > rf.commitIndex {
                if args.leaderCommit > lastIndex {
                    rf.commitIndex = lastIndex
                } else {
                    rf.commitIndex = args.leaderCommit
                }
            }
            // commit ?
            if conflict {
                rf.lastLogTerm = rf.log[lastIndex].term
                rf.lastLogIndex = lastIndex
                for {
                    lastIndex ++
                    if _, ok := rf.log[lastIndex]; ok {
                        delete(rf.log, lastIndex)
                    } else {
                        break
                    }
                }
            } else {
                if rf.lastLogTerm < lastIndex {
                    rf.lastLogIndex = lastIndex
                    rf.lastLogTerm = rf.log[lastIndex].term
                }
            }
        } else {
            reply.success = false
        }
    }
    req.replyCh <- reply
    return reEnter
}

func (rf *Raft)handle_evRequestVote(req *reqEvent) bool {
    var reEnter bool
    args := req.args.(RequestVoteArgs)
    reply := RequestVoteReply{}
    if args.term < rf.currentTerm {
        reEnter = false
        reply.term = rf.currentTerm
        reply.voteGranted = false
    } else if args.term == rf.currentTerm {
        if (rf.votedFor == args.candidateId || rf.votedFor == -1) && (args.lastLogTerm >= rf.lastLogTerm || args.lastLogIndex >= rf.lastLogIndex) {
            reEnter = true
            rf.state = Follower
            reply.term = args.term
            reply.voteGranted = true
        } else {
            reEnter = false
            reply.term = rf.currentTerm
            reply.voteGranted = false
        }
    } else {
        reEnter = true
        rf.state = Follower
        rf.term = args.term
        reply.term = args.term
        if args.lastLogTerm >= rf.lastLogTerm || args.lastLogIndex >= rf.lastLogIndex {
            reply.voteGranted = true
        } else {
            reply.voteGranted = false
        }
    }
    req.replyCh <- reply
    return reEnter
}

func (rf *Raft)handle_evGetState(req *reqEvent) bool {
    reply := replyState{}
    reply.term = rf.currentTerm
    if state == Leader {
        reply.isleader = true
    } else {
        reply.isleader = false
    }
    req.replyCh <- reply
    return false
}

func (rf *Raft)handle_evStartCommand(req *reqEvent) bool {
    reply := replyStart{}
    if rf.state != Leader {
        reply.isLeader = false
    } else {
        reply.isLeader = true
        rf.lastLogIndex ++
        rf.lastLogTerm = rf.currentTerm
        rf.log[rf.lastLogIndex] = Entry{term: rf.currentTerm, command: req.args}
    }
    req.replyCh <- reply
    return false
}

func (rf *Raft) handle_event(req *reqEvent) bool{
    var reEnter bool
    switch req.evType {
    case evAppendEntry:
        reEnter = rf.handle_evAppendEntry(req)
    case evRequestVote:
        reEnter = rf.handle_evRequestVote(req)
    case evGetState:
        reEnter = rf.handle_evGetState(req)
    case evStartCommand:
        reEnter = rf.handle_evStateCommand(req)
    }
    return reEnter
}

func (rf *Raft) run_as_follower() {
    seed := rand.NewSource(time.Now().Unix())
    r := rand.New(seed)
    du := 400 + r.Intn(600)

    now := time.Now()
    endtime := now.Add(time.Duration(du)*time.Millisecond)
    for time.Now().Before(endtime) {
        select {
        case req := <- rf.eventCh:
            if true == rf.handle_event(&req) {
                return;
            }
        case <- time.After(time.Millisecond*100):

        }
    }
    rf.state = Candidate
    rf.currentTerm ++
    rf.votedFor = me
}

type RpcType int

const (
    rpcAppendEntry  RpcType = iota
    rpcRequestVote
)

type reqRpc struct {
    rpcType     RpcType
    args        interface{}
    replyCh     chan interface
}

type rpcReply struct {
    success     bool
    server      int
    reply       interface{}
}

func (rf *Raft) rpcWrapper(server int, req *reqRpc) {
    wrapperReply := rpcReply{}
    wrapperReply.server = server
    if req.rpcType == rpcAppendEntry {
        reply := AppendEntryReply{}
        ok := rf.sendAppendEntry(server, &(req.args.(AppendEntryArgs)), &reply)
        wrapperReply.success = ok
        wrapperReply.reply = reply
    } else if req.rpcType == rpcRequestVote {
        reply := RequestVoteReply{}
        ok := rf.sendRequestVote(server, &(req.args.(RequestVoteArgs)), &reply)
        wrapperReply.success = ok
        wrapperReply.reply = reply
    } else {
    //error
    }
    req.replyCh <- wrapperReply
}

func (rf *Raft) run_for_leader(ch chan bool) {
    commonCh := chan interface{}
    numSent := 0
    for i, peer := range rf.peers {
        if i != rf.me {
            numSent ++
            args := RequestVoteArgs{}
            args.term = rf.currentTerm
            args.candidateId = rf.me
            args.lastLogIndex = rf.lastLogIndex
            args.lastLogTerm = rf.lastLogTerm

            req := reqRpc{}
            req.rpcType = rpcRequestVote
            req.args = args
            req.replyCh = commonCh
            go rf.rpcWrapper(peer, &req)
        }
    }
    commonReply := rpcReply{}
    outdated := false
    numGranted := 0
    for i:=0; i != numSent; i ++ {
        commonReply = (<-commonCh).(rpcReply)
        if commonReply.success == false {
            continue
        }
        requestReply := commonReply.reply.(RequestVoteReply)
        if requestReply.term > rf.currentTerm {
            outdated = true
            continue
        }
        if requestReply.voteGranted == true {
            numGranted ++
        }
    }
    if outdated == true {
        rf.state = Follower
        return
    }
    if  
}

func (rf *Raft) broadcast() {
    commonCh := chan interface{}
    numSent := 0
    for i, peer := range rf.peers {
        if i != rf.me {
            numSent ++
            args := AppendEntryArgs{}
            args.term = rf.currentTerm
            args.leaderId = rf.me
            args.prevLogIndex = rf.nextIndex[i]-1
            args.prevLogTerm = rf.log[args.prevLogIndex].term
            entries := make(map[int]Entry)
            if rf.nextIndex[i] <= rf.lastLogIndex {
                entries[rf.nextIndex[i]] = rf.log[rf.nextIndex[i]]
            }
            rf.entries = entries
            args.leaderCommit = rf.commitIndex

            req := reqRpc{}
            req.rpcType = rpcAppendEntry
            req.args = args
            req.replyCh = commonCh
            go rf.rpcWrapper(peer, &req)
        }
    }
    commonReply := rpcReply{}
    outdated := false
    numSuccess := 0
    for i:=0;i != numSent; i ++ {
        commonReply = (<- commonCh).(rpcReply)
        if commonReply.success == false {
            continue
        }
        appendReply := commonReply.reply.(AppendEntryReply)
        if appendReply.term > rf.currentTerm {
            outdated := true
            continue
        }
        if appendReply.success == true {
            numSuccess ++
            rf.matchIndex[i] = rf.nextIndex[i]
            rf.nextIndex[i] ++
        } else {
            if rf.nextIndex[i] < 1 {
                //report
            }
            rf.nextIndex[i] --
        }
    }
    if outdated = true {
        rf.state = Follower
    } else if numSuccess >
}

func (rf *Raft) run_as_candidate() {
    seed := rand.NewSource(time.Now().Unix())
    r := rand.New(seed)
    du := 400 + r.Intn(600)
    now := time.Now()
    endtime := now.Add(time.Duration(du)*time.Millisecond)
    result := make(chan bool, 1)
    for time.Now().Before(endtime) {
        go rf.run_for_leader(result)
        select {
        case req := <- rf.eventCh:
            if true == rf.handle_event(&req){
                return;
            }
        case eleted := <- result:
            rf.state = Leader
            return
        case time.After(time.Millisecond*300):
        }
    }
    rf.currentTerm ++
    rf.votedFor = me
}

func (rf *Raft) sendAppendEntry(server int, args *AppendEntryArgs, reply *AppendEntryReply
    ok := rf.peers[server].Call("Raft.AppendEntry", args, reply)
    return ok
}

func (rf *Raft) run_as_leader() {
    for {
        rf.broadcast()
        select {
        case req := <-rf.eventCh:
            if true == rf.handle_event(&req){
                return;
            }
        case time.After(time.Millisecond*BROADCAST_INTERVAL)
        }
    }
}

func (rf *Raft) run() {
    for {
        switch rf.state {
        case Follower:
            rf.run_as_follower()
        case Candidate:
            rf.run_as_candidate()
        case Leader:
            rf.run_as_leader()
        default:
            // TODO
        }
    }
}

func Make(peers []*labrpc.ClientEnd, me int,
	persister *Persister, applyCh chan ApplyMsg) *Raft {
	rf := &Raft{}
	rf.peers = peers
	rf.persister = persister
	rf.me = me
    rf.eventCh = make(chan reqEvent)
    go rf.run()

	// Your initialization code here (2A, 2B, 2C).

	// initialize from state persisted before a crash
	rf.readPersist(persister.ReadRaftState())

	return rf
}
