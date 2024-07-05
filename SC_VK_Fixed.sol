// SPDX-License-Identifier: MIT
pragma solidity ^0.4.8;

contract OTPToekn {
    uint n;
    bytes32 userVerifyKey;

    constructor(bytes32 vk){
        userVerifyKey = vk;
        n = 1;
    }

    function Proxy(bytes32 Token, bytes memory nonce) public returns(bool){
        
        bytes32 proxyVerifyKey = sha256(abi.encodePacked(nonce,msg.sender));

        for(uint i = 0; i < 4; i++){
            if(proxyVerifyKey[i] != Token[i])
                return false;
        }

        for(i = 0; i < 1000 - n; i++){
            Token = sha256(Token);
        }

        if(Token == userVerifyKey){
            n = n + 1;
            return true;
        } else {
            n = n + 1;
            return false;
        }
    }
}