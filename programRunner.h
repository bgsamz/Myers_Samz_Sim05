void runPrograms(struct PCB * programPCBs, int numPrograms, struct Config config);
void runFCFS_N(struct PCB * programPCBs, int numPrograms, struct Config config);
void runSJF_N(struct PCB * programPCBs, int numPrograms, struct Config config);
void runAction(struct PCB currPro, struct Action currAct, struct Config config);
void sortPrograms(struct Config config, struct PCB * programs, int numPrograms);
