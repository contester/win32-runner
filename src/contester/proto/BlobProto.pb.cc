// Generated by the protocol buffer compiler.  DO NOT EDIT!

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "contester/proto/BlobProto.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace contester {
namespace proto {

namespace {

const ::google::protobuf::Descriptor* Blob_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Blob_reflection_ = NULL;
const ::google::protobuf::Descriptor* Blob_CompressionInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Blob_CompressionInfo_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* Blob_CompressionInfo_CompressionType_descriptor_ = NULL;
const ::google::protobuf::Descriptor* File_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  File_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_contester_2fproto_2fBlobProto_2eproto() {
  protobuf_AddDesc_contester_2fproto_2fBlobProto_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "contester/proto/BlobProto.proto");
  GOOGLE_CHECK(file != NULL);
  Blob_descriptor_ = file->message_type(0);
  static const int Blob_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Blob, data_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Blob, compression_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Blob, sha1_),
  };
  Blob_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Blob_descriptor_,
      Blob::default_instance_,
      Blob_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Blob, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Blob, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Blob));
  Blob_CompressionInfo_descriptor_ = Blob_descriptor_->nested_type(0);
  static const int Blob_CompressionInfo_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Blob_CompressionInfo, method_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Blob_CompressionInfo, original_size_),
  };
  Blob_CompressionInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Blob_CompressionInfo_descriptor_,
      Blob_CompressionInfo::default_instance_,
      Blob_CompressionInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Blob_CompressionInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Blob_CompressionInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Blob_CompressionInfo));
  Blob_CompressionInfo_CompressionType_descriptor_ = Blob_CompressionInfo_descriptor_->enum_type(0);
  File_descriptor_ = file->message_type(1);
  static const int File_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(File, name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(File, data_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(File, type_),
  };
  File_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      File_descriptor_,
      File::default_instance_,
      File_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(File, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(File, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(File));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_contester_2fproto_2fBlobProto_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Blob_descriptor_, &Blob::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Blob_CompressionInfo_descriptor_, &Blob_CompressionInfo::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    File_descriptor_, &File::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_contester_2fproto_2fBlobProto_2eproto() {
  delete Blob::default_instance_;
  delete Blob_reflection_;
  delete Blob_CompressionInfo::default_instance_;
  delete Blob_CompressionInfo_reflection_;
  delete File::default_instance_;
  delete File_reflection_;
}

void protobuf_AddDesc_contester_2fproto_2fBlobProto_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\037contester/proto/BlobProto.proto\022\017conte"
    "ster.proto\"\205\002\n\004Blob\022\014\n\004data\030\001 \001(\014\022:\n\013com"
    "pression\030\002 \001(\0132%.contester.proto.Blob.Co"
    "mpressionInfo\022\014\n\004sha1\030\003 \001(\014\032\244\001\n\017Compress"
    "ionInfo\022E\n\006method\030\001 \001(\01625.contester.prot"
    "o.Blob.CompressionInfo.CompressionType\022\025"
    "\n\roriginal_size\030\002 \001(\r\"3\n\017CompressionType"
    "\022\017\n\013METHOD_NONE\020\000\022\017\n\013METHOD_ZLIB\020\001\"G\n\004Fi"
    "le\022\014\n\004name\030\001 \002(\t\022#\n\004data\030\002 \002(\0132\025.contest"
    "er.proto.Blob\022\014\n\004type\030\003 \002(\t", 387);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "contester/proto/BlobProto.proto", &protobuf_RegisterTypes);
  Blob::default_instance_ = new Blob();
  Blob_CompressionInfo::default_instance_ = new Blob_CompressionInfo();
  File::default_instance_ = new File();
  Blob::default_instance_->InitAsDefaultInstance();
  Blob_CompressionInfo::default_instance_->InitAsDefaultInstance();
  File::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_contester_2fproto_2fBlobProto_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_contester_2fproto_2fBlobProto_2eproto {
  StaticDescriptorInitializer_contester_2fproto_2fBlobProto_2eproto() {
    protobuf_AddDesc_contester_2fproto_2fBlobProto_2eproto();
  }
} static_descriptor_initializer_contester_2fproto_2fBlobProto_2eproto_;


// ===================================================================

const ::google::protobuf::EnumDescriptor* Blob_CompressionInfo_CompressionType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Blob_CompressionInfo_CompressionType_descriptor_;
}
bool Blob_CompressionInfo_CompressionType_IsValid(int value) {
  switch(value) {
    case 0:
    case 1:
      return true;
    default:
      return false;
  }
}

#ifndef _MSC_VER
const Blob_CompressionInfo_CompressionType Blob_CompressionInfo::METHOD_NONE;
const Blob_CompressionInfo_CompressionType Blob_CompressionInfo::METHOD_ZLIB;
const Blob_CompressionInfo_CompressionType Blob_CompressionInfo::CompressionType_MIN;
const Blob_CompressionInfo_CompressionType Blob_CompressionInfo::CompressionType_MAX;
const int Blob_CompressionInfo::CompressionType_ARRAYSIZE;
#endif  // _MSC_VER
#ifndef _MSC_VER
const int Blob_CompressionInfo::kMethodFieldNumber;
const int Blob_CompressionInfo::kOriginalSizeFieldNumber;
#endif  // !_MSC_VER

Blob_CompressionInfo::Blob_CompressionInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Blob_CompressionInfo::InitAsDefaultInstance() {
}

Blob_CompressionInfo::Blob_CompressionInfo(const Blob_CompressionInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Blob_CompressionInfo::SharedCtor() {
  _cached_size_ = 0;
  method_ = 0;
  original_size_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Blob_CompressionInfo::~Blob_CompressionInfo() {
  SharedDtor();
}

void Blob_CompressionInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Blob_CompressionInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Blob_CompressionInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Blob_CompressionInfo_descriptor_;
}

const Blob_CompressionInfo& Blob_CompressionInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_contester_2fproto_2fBlobProto_2eproto();  return *default_instance_;
}

Blob_CompressionInfo* Blob_CompressionInfo::default_instance_ = NULL;

Blob_CompressionInfo* Blob_CompressionInfo::New() const {
  return new Blob_CompressionInfo;
}

void Blob_CompressionInfo::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    method_ = 0;
    original_size_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Blob_CompressionInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .contester.proto.Blob.CompressionInfo.CompressionType method = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::contester::proto::Blob_CompressionInfo_CompressionType_IsValid(value)) {
            set_method(static_cast< ::contester::proto::Blob_CompressionInfo_CompressionType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_original_size;
        break;
      }
      
      // optional uint32 original_size = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_original_size:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &original_size_)));
          set_has_original_size();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Blob_CompressionInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional .contester.proto.Blob.CompressionInfo.CompressionType method = 1;
  if (has_method()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->method(), output);
  }
  
  // optional uint32 original_size = 2;
  if (has_original_size()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->original_size(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Blob_CompressionInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional .contester.proto.Blob.CompressionInfo.CompressionType method = 1;
  if (has_method()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->method(), target);
  }
  
  // optional uint32 original_size = 2;
  if (has_original_size()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->original_size(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Blob_CompressionInfo::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .contester.proto.Blob.CompressionInfo.CompressionType method = 1;
    if (has_method()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->method());
    }
    
    // optional uint32 original_size = 2;
    if (has_original_size()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->original_size());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Blob_CompressionInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Blob_CompressionInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Blob_CompressionInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Blob_CompressionInfo::MergeFrom(const Blob_CompressionInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_method()) {
      set_method(from.method());
    }
    if (from.has_original_size()) {
      set_original_size(from.original_size());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Blob_CompressionInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Blob_CompressionInfo::CopyFrom(const Blob_CompressionInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Blob_CompressionInfo::IsInitialized() const {
  
  return true;
}

void Blob_CompressionInfo::Swap(Blob_CompressionInfo* other) {
  if (other != this) {
    std::swap(method_, other->method_);
    std::swap(original_size_, other->original_size_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Blob_CompressionInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Blob_CompressionInfo_descriptor_;
  metadata.reflection = Blob_CompressionInfo_reflection_;
  return metadata;
}


// -------------------------------------------------------------------

#ifndef _MSC_VER
const int Blob::kDataFieldNumber;
const int Blob::kCompressionFieldNumber;
const int Blob::kSha1FieldNumber;
#endif  // !_MSC_VER

Blob::Blob()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Blob::InitAsDefaultInstance() {
  compression_ = const_cast< ::contester::proto::Blob_CompressionInfo*>(&::contester::proto::Blob_CompressionInfo::default_instance());
}

Blob::Blob(const Blob& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Blob::SharedCtor() {
  _cached_size_ = 0;
  data_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  compression_ = NULL;
  sha1_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Blob::~Blob() {
  SharedDtor();
}

void Blob::SharedDtor() {
  if (data_ != &::google::protobuf::internal::kEmptyString) {
    delete data_;
  }
  if (sha1_ != &::google::protobuf::internal::kEmptyString) {
    delete sha1_;
  }
  if (this != default_instance_) {
    delete compression_;
  }
}

void Blob::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Blob::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Blob_descriptor_;
}

const Blob& Blob::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_contester_2fproto_2fBlobProto_2eproto();  return *default_instance_;
}

Blob* Blob::default_instance_ = NULL;

Blob* Blob::New() const {
  return new Blob;
}

void Blob::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_data()) {
      if (data_ != &::google::protobuf::internal::kEmptyString) {
        data_->clear();
      }
    }
    if (has_compression()) {
      if (compression_ != NULL) compression_->::contester::proto::Blob_CompressionInfo::Clear();
    }
    if (has_sha1()) {
      if (sha1_ != &::google::protobuf::internal::kEmptyString) {
        sha1_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Blob::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional bytes data = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_data()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_compression;
        break;
      }
      
      // optional .contester.proto.Blob.CompressionInfo compression = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_compression:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_compression()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_sha1;
        break;
      }
      
      // optional bytes sha1 = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_sha1:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_sha1()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Blob::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional bytes data = 1;
  if (has_data()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      1, this->data(), output);
  }
  
  // optional .contester.proto.Blob.CompressionInfo compression = 2;
  if (has_compression()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->compression(), output);
  }
  
  // optional bytes sha1 = 3;
  if (has_sha1()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      3, this->sha1(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Blob::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional bytes data = 1;
  if (has_data()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        1, this->data(), target);
  }
  
  // optional .contester.proto.Blob.CompressionInfo compression = 2;
  if (has_compression()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->compression(), target);
  }
  
  // optional bytes sha1 = 3;
  if (has_sha1()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        3, this->sha1(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Blob::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional bytes data = 1;
    if (has_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->data());
    }
    
    // optional .contester.proto.Blob.CompressionInfo compression = 2;
    if (has_compression()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->compression());
    }
    
    // optional bytes sha1 = 3;
    if (has_sha1()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->sha1());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Blob::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Blob* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Blob*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Blob::MergeFrom(const Blob& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_data()) {
      set_data(from.data());
    }
    if (from.has_compression()) {
      mutable_compression()->::contester::proto::Blob_CompressionInfo::MergeFrom(from.compression());
    }
    if (from.has_sha1()) {
      set_sha1(from.sha1());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Blob::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Blob::CopyFrom(const Blob& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Blob::IsInitialized() const {
  
  return true;
}

void Blob::Swap(Blob* other) {
  if (other != this) {
    std::swap(data_, other->data_);
    std::swap(compression_, other->compression_);
    std::swap(sha1_, other->sha1_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Blob::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Blob_descriptor_;
  metadata.reflection = Blob_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int File::kNameFieldNumber;
const int File::kDataFieldNumber;
const int File::kTypeFieldNumber;
#endif  // !_MSC_VER

File::File()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void File::InitAsDefaultInstance() {
  data_ = const_cast< ::contester::proto::Blob*>(&::contester::proto::Blob::default_instance());
}

File::File(const File& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void File::SharedCtor() {
  _cached_size_ = 0;
  name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  data_ = NULL;
  type_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

File::~File() {
  SharedDtor();
}

void File::SharedDtor() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (type_ != &::google::protobuf::internal::kEmptyString) {
    delete type_;
  }
  if (this != default_instance_) {
    delete data_;
  }
}

void File::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* File::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return File_descriptor_;
}

const File& File::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_contester_2fproto_2fBlobProto_2eproto();  return *default_instance_;
}

File* File::default_instance_ = NULL;

File* File::New() const {
  return new File;
}

void File::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_name()) {
      if (name_ != &::google::protobuf::internal::kEmptyString) {
        name_->clear();
      }
    }
    if (has_data()) {
      if (data_ != NULL) data_->::contester::proto::Blob::Clear();
    }
    if (has_type()) {
      if (type_ != &::google::protobuf::internal::kEmptyString) {
        type_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool File::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string name = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->name().data(), this->name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_data;
        break;
      }
      
      // required .contester.proto.Blob data = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_data:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_data()));
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(26)) goto parse_type;
        break;
      }
      
      // required string type = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_type:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_type()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->type().data(), this->type().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }
      
      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void File::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->name(), output);
  }
  
  // required .contester.proto.Blob data = 2;
  if (has_data()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->data(), output);
  }
  
  // required string type = 3;
  if (has_type()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->type().data(), this->type().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->type(), output);
  }
  
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* File::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string name = 1;
  if (has_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->name(), target);
  }
  
  // required .contester.proto.Blob data = 2;
  if (has_data()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->data(), target);
  }
  
  // required string type = 3;
  if (has_type()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->type().data(), this->type().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->type(), target);
  }
  
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int File::ByteSize() const {
  int total_size = 0;
  
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string name = 1;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->name());
    }
    
    // required .contester.proto.Blob data = 2;
    if (has_data()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->data());
    }
    
    // required string type = 3;
    if (has_type()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->type());
    }
    
  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void File::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const File* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const File*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void File::MergeFrom(const File& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_data()) {
      mutable_data()->::contester::proto::Blob::MergeFrom(from.data());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void File::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void File::CopyFrom(const File& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool File::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  
  return true;
}

void File::Swap(File* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(data_, other->data_);
    std::swap(type_, other->type_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata File::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = File_descriptor_;
  metadata.reflection = File_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace contester

// @@protoc_insertion_point(global_scope)
