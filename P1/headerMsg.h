
struct headerMsg{
    int functionName; // TYpe of mensage
    int sizePayload; 			//Total Bytes of Payload
    char payload[100];			//Pointer for any structure
};

#define sizeFunctionName 4
