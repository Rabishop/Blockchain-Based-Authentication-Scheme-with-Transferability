// SPDX-License-Identifier: MIT
pragma solidity ^0.4.8;

contract ECVerify {

    bytes pk;

    constructor(bytes PK){
        pk = new bytes(128);
        pk = PK;
    }



    event VerifyResult(bool ret, address indexed addr, address indexed recoverAddress);

    function verify(bytes32 hash, uint8 v, bytes32 r, bytes32 s, address signer) returns(bool) {
        bytes32 pkhash = keccak256(pk);
        if(address(pkhash) != signer)
            ret = false;

        bytes memory prefix = "\x19Ethereum Signed Message:\n32";
        bytes32 prefixedHash = sha3(prefix, hash);

        bool ret = false;
        address recoverAddress = ecrecover(prefixedHash, v, r, s);

        if (recoverAddress == signer)
            ret = true;

        VerifyResult(ret, signer, recoverAddress);

        return ret;

    }
}