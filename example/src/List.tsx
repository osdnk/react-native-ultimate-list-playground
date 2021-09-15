import React, {
  useCallback,
  useRef,
  useState,
  createContext,
  useContext,
} from 'react';
import { View, Text, StyleSheet, ViewStyle, Button } from 'react-native';
import {
  RecyclerListView,
  RecyclerRow as RawRecyclerRow,
  UltraFastTextWrapper,
} from './ultimate';
import { data, DataCell } from './data';
import Animated, {
  useSharedValue,
  useDerivedValue,
  useAnimatedStyle,
} from 'react-native-reanimated';
import { useAnimatedRecycleHandler } from './useAnimatedRecycleEvent';
import { ReText } from 'react-native-redash';

const DataContext = createContext<any[] | null>(null);
const PositionContext = createContext<Animated.SharedValue<number> | null>(
  null
);

const AnimatedRecyclableRow = Animated.createAnimatedComponent(RawRecyclerRow);

function usePosition() {
  return useContext(PositionContext);
}

function useData() {
  return useContext(DataContext);
}

function useSharedDataAtIndex() {
  const data = useData();
  const position = usePosition();
  // matbo copy the data and not access them on every recycle
  return useDerivedValue(() => data?.[position?.value ?? -1], [data]);
}

function RecyclerRow(props) {
  const position = useSharedValue<number>(-1);
  const onRecycleHandler = useAnimatedRecycleHandler((e) => {
    'worklet';
    position.value = e.position;
  });

  return (
    <PositionContext.Provider value={position}>
      <AnimatedRecyclableRow {...props} onRecycle={onRecycleHandler} />
    </PositionContext.Provider>
  );
}

const namingHandler = {
  get(
    { binding }: { binding: string },
    property: string
  ): { binding: string } | string {
    if (property === '___binding') {
      return binding;
    }
    return new Proxy(
      { binding: binding === '' ? property : `${binding}.${property}` },
      namingHandler
    );
  },
};

function useUltraFastData<TCellData extends object>() {
  return new Proxy({ binding: '' }, namingHandler) as any as TCellData;
}

function UltraFastText({ binding }: { binding: string }) {
  return (
    // @ts-ignore
    <UltraFastTextWrapper binding={binding.___binding}>
      <Text style={{ width: 100 }} />
    </UltraFastTextWrapper>
  );
}


// const List = createList<Data>();
// const { WrapperList, useUltraFastSomething, useSharedDataAtIndex, useData } = List;

function ContactCell() {
  const data = useSharedDataAtIndex();
  const text = useDerivedValue(() => data.value?.name ?? '');
  const color = useDerivedValue(() => {
    const name = data.value?.name ?? '';
    const colors = ['red', 'green', 'blue', 'white', 'yellow'];
    let hash = 0,
      i,
      chr;
    if (name.length === 0) return hash;
    for (i = 0; i < name.length - 2; i++) {
      chr = name.charCodeAt(i);
      hash = (hash << 5) - hash + chr;
      hash |= 0;
    }
    return colors[Math.abs(hash) % 5];
  });
  const circleStyle = useAnimatedStyle(() => ({
    backgroundColor: color.value,
  }));

  const {
    nested: { prof },
    name
  } = useUltraFastData<DataCell>(); // const prof = "nested.prof"

  return (
    <View
      style={{
        borderWidth: 2,
        backgroundColor: 'grey',
        height: 100,
        justifyContent: 'center',
        alignItems: 'center',
        flexDirection: 'row',
      }}
    >
      <Animated.View
        style={[
          circleStyle,
          {
            width: 60,
            height: 60,
            borderRadius: 30,
            marginRight: 20,
          },
        ]}
      />
      <UltraFastText binding={name} />
      {/*<UltraFastSwtich binding={"type"} >*/}
      {/*  <UltraFastCase type="loading"/>*/}
      {/*</UltraFastSwtich>*/}


      {/*<UltraFastText binding={name} />*/}
      <ReText text={text} />

      {/*<RecyclableText style={{ width: '70%' }}>Beata Kozidrak</RecyclableText>*/}
    </View>
  );
}

function RecyclableViews({ children }: { children: React.ReactChild }) {
  return (
    <View removeClippedSubviews={false} style={{ opacity: 1 }}>
      {/* TODO make better render counting  */}
      {[...Array(8)].map((_, key) => (
        <RecyclerRow
          onRecycle={console.log}
          removeClippedSubviews={false}
          key={`rl-${key}`}
        >
          {children}
        </RecyclerRow>
      ))}
    </View>
  );
}

function RecyclerView<TData>({
  style,
  children,
}: {
  style: ViewStyle;
  children: any;
  data: TData[];
}) {
  // @ts-ignore
  global.recyclableData = data;
  return (
    <DataContext.Provider value={data}>
      <View style={style} removeClippedSubviews={false}>
        <RecyclableViews>{children}</RecyclableViews>
        <RecyclerListView
          count={data.length}
          style={StyleSheet.absoluteFillObject}
        />
      </View>
    </DataContext.Provider>
  );
}




export default function Example() {
  // const layoutProvider = useLayoutProvider(() => ({
  //   contact: <ContactCell />,
  //   call: <CallView/>
  // }))

  //
  // const layoutProvider = useMemo(() => ({
  //   contact: <ContactCell />,
  //   call: <CallView/>
  // }), [])

  //const layoutTypeExtractor = useLayoutTypeExtractor(item =>  item.name)

  return (
    <RecyclerView<DataCell>
    //  layoutProvider={layoutProvider}
      //layoutTypeExtractor={layoutTypeExtractor} // all called before rendering
      data={data} style={{ width: '100%', height: 300 }}
     //layoutProvider={layoutProvider}
    >
      <ContactCell />
    </RecyclerView>
  );
}
