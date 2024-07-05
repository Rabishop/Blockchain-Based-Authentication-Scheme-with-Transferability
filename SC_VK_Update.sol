// SPDX-License-Identifier: MIT
pragma solidity ^0.4.8;

contract OTPToekn {
    bytes32 userVerifyKey;

    constructor(bytes32 vk){
        userVerifyKey = vk;
    }

    function Proxy(bytes32 Token, bytes memory nonce) public returns(bool){
        
        bytes32 proxyVerifyKey = sha256(abi.encodePacked(nonce,msg.sender));

        for(uint i = 0; i < 4; i++){
            if(proxyVerifyKey[i] != Token[i])
                return false;
        }

        Token_sha256 = sha256(Token);

        if(Token_sha256 == userVerifyKey){
            userVerifyKey = Token
            return true;
        } else {
            return false;
        }
    }
}